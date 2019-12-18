#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_int ;
struct TYPE_4__ {int /*<<< orphan*/ * iops; } ;
struct bcm_nvram_iocfe {char* dname; scalar_t__ fd; int req_blk_erase; void* size; void* offset; TYPE_1__ io; } ;
struct TYPE_5__ {void* nvram_size; scalar_t__ nvram_offset; scalar_t__ nvram_eraseflg; } ;
typedef  TYPE_2__ nvram_info_t ;
typedef  int /*<<< orphan*/  nvram_info ;
typedef  scalar_t__ intmax_t ;
typedef  void* int64_t ;
struct TYPE_6__ {int flash_flags; void* flash_size; } ;
typedef  TYPE_3__ flash_info_t ;
typedef  int /*<<< orphan*/  fi ;

/* Variables and functions */
#define  CFE_DEV_FLASH 129 
 int CFE_DEV_MASK ; 
#define  CFE_DEV_NVRAM 128 
 int CFE_ERR_INV_COMMAND ; 
 int CFE_OK ; 
 int ENXIO ; 
 int FLASH_FLAG_NOERASE ; 
 int /*<<< orphan*/  IOCFE_LOG (struct bcm_nvram_iocfe*,char*,void*,...) ; 
 int /*<<< orphan*/  IOCTL_FLASH_GETINFO ; 
 int /*<<< orphan*/  IOCTL_NVRAM_GETINFO ; 
 void* SIZE_MAX ; 
 int /*<<< orphan*/  bhnd_nvram_iocfe_ops ; 
 int /*<<< orphan*/  cfe_close (scalar_t__) ; 
 int cfe_getdevinfo (char*) ; 
 int cfe_ioctl (scalar_t__,int /*<<< orphan*/ ,unsigned char*,int,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ cfe_open (char*) ; 

__attribute__((used)) static int
bcm_nvram_iocfe_init(struct bcm_nvram_iocfe *iocfe, char *dname)
{
	nvram_info_t		 nvram_info;
	int			 cerr, devinfo, dtype, rlen;
	int64_t			 nv_offset;
	u_int			 nv_size;
	bool			 req_blk_erase;
	int			 error;

	iocfe->io.iops = &bhnd_nvram_iocfe_ops;
	iocfe->dname = dname;

	/* Try to open the device */
	iocfe->fd = cfe_open(dname);
	if (iocfe->fd <= 0) {
		IOCFE_LOG(iocfe, "cfe_open() failed: %d\n", iocfe->fd);

		return (ENXIO);
	}

	/* Try to fetch device info */
	if ((devinfo = cfe_getdevinfo(iocfe->dname)) < 0) {
		IOCFE_LOG(iocfe, "cfe_getdevinfo() failed: %d\n", devinfo);
		error = ENXIO;
		goto failed;
	}

	/* Verify device type */
	dtype = devinfo & CFE_DEV_MASK;
	switch (dtype) {
	case CFE_DEV_FLASH:
	case CFE_DEV_NVRAM:
		/* Valid device type */
		break;
	default:
		IOCFE_LOG(iocfe, "unknown device type: %d\n", dtype);
		error = ENXIO;
		goto failed;
	}

	/* Try to fetch nvram info from CFE */
	cerr = cfe_ioctl(iocfe->fd, IOCTL_NVRAM_GETINFO,
	    (unsigned char *)&nvram_info, sizeof(nvram_info), &rlen, 0);
	if (cerr == CFE_OK) {
		/* Sanity check the result; must not be a negative integer */
		if (nvram_info.nvram_size < 0 ||
		    nvram_info.nvram_offset < 0)
		{
			IOCFE_LOG(iocfe, "invalid NVRAM layout (%d/%d)\n",
			    nvram_info.nvram_size, nvram_info.nvram_offset);
			error = ENXIO;
			goto failed;
		}

		nv_offset	= nvram_info.nvram_offset;
		nv_size		= nvram_info.nvram_size;
		req_blk_erase	= (nvram_info.nvram_eraseflg != 0);
	} else if (cerr != CFE_OK && cerr != CFE_ERR_INV_COMMAND) {
		IOCFE_LOG(iocfe, "IOCTL_NVRAM_GETINFO failed: %d\n", cerr);
		error = ENXIO;
		goto failed;
	}

	/* Fall back on flash info.
	 * 
	 * This is known to be required on the Asus RT-N53 (CFE 5.70.55.33, 
	 * BBP 1.0.37, BCM5358UB0), where IOCTL_NVRAM_GETINFO returns
	 * CFE_ERR_INV_COMMAND.
	 */
	if (cerr == CFE_ERR_INV_COMMAND) {
		flash_info_t fi;

		cerr = cfe_ioctl(iocfe->fd, IOCTL_FLASH_GETINFO,
		    (unsigned char *)&fi, sizeof(fi), &rlen, 0);

		if (cerr != CFE_OK) {
			IOCFE_LOG(iocfe, "IOCTL_FLASH_GETINFO failed %d\n",
			    cerr);
			error = ENXIO;
			goto failed;
		}

		nv_offset	= 0x0;
		nv_size		= fi.flash_size;
		req_blk_erase	= !(fi.flash_flags & FLASH_FLAG_NOERASE);
	}

	
	/* Verify that the full NVRAM layout can be represented via size_t */
	if (nv_size > SIZE_MAX || SIZE_MAX - nv_size < nv_offset) {
		IOCFE_LOG(iocfe, "invalid NVRAM layout (%#x/%#jx)\n",
		    nv_size, (intmax_t)nv_offset);
		error = ENXIO;
		goto failed;
	}

	iocfe->offset = nv_offset;
	iocfe->size = nv_size;
	iocfe->req_blk_erase = req_blk_erase;

	return (CFE_OK);

failed:
	if (iocfe->fd >= 0)
		cfe_close(iocfe->fd);

	return (error);
}
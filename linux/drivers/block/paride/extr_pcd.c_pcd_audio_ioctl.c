#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcd_unit {int dummy; } ;
struct cdrom_tochdr {char cdth_trk0; char cdth_trk1; } ;
struct TYPE_3__ {unsigned char minute; unsigned char second; unsigned char frame; } ;
struct TYPE_4__ {unsigned char lba; TYPE_1__ msf; } ;
struct cdrom_tocentry {char cdte_track; unsigned char cdte_ctrl; unsigned char cdte_adr; int cdte_datamode; TYPE_2__ cdte_addr; int /*<<< orphan*/  cdte_format; } ;
struct cdrom_device_info {struct pcd_unit* handle; } ;

/* Variables and functions */
#define  CDROMREADTOCENTRY 129 
#define  CDROMREADTOCHDR 128 
 int /*<<< orphan*/  CDROM_MSF ; 
 int EIO ; 
 int ENOSYS ; 
 int GPCMD_READ_TOC_PMA_ATIP ; 
 int pcd_atapi (struct pcd_unit*,char*,int,...) ; 

__attribute__((used)) static int pcd_audio_ioctl(struct cdrom_device_info *cdi, unsigned int cmd, void *arg)
{
	struct pcd_unit *cd = cdi->handle;

	switch (cmd) {

	case CDROMREADTOCHDR:

		{
			char cmd[12] =
			    { GPCMD_READ_TOC_PMA_ATIP, 0, 0, 0, 0, 0, 0, 0, 12,
			 0, 0, 0 };
			struct cdrom_tochdr *tochdr =
			    (struct cdrom_tochdr *) arg;
			char buffer[32];
			int r;

			r = pcd_atapi(cd, cmd, 12, buffer, "read toc header");

			tochdr->cdth_trk0 = buffer[2];
			tochdr->cdth_trk1 = buffer[3];

			return r ? -EIO : 0;
		}

	case CDROMREADTOCENTRY:

		{
			char cmd[12] =
			    { GPCMD_READ_TOC_PMA_ATIP, 0, 0, 0, 0, 0, 0, 0, 12,
			 0, 0, 0 };

			struct cdrom_tocentry *tocentry =
			    (struct cdrom_tocentry *) arg;
			unsigned char buffer[32];
			int r;

			cmd[1] =
			    (tocentry->cdte_format == CDROM_MSF ? 0x02 : 0);
			cmd[6] = tocentry->cdte_track;

			r = pcd_atapi(cd, cmd, 12, buffer, "read toc entry");

			tocentry->cdte_ctrl = buffer[5] & 0xf;
			tocentry->cdte_adr = buffer[5] >> 4;
			tocentry->cdte_datamode =
			    (tocentry->cdte_ctrl & 0x04) ? 1 : 0;
			if (tocentry->cdte_format == CDROM_MSF) {
				tocentry->cdte_addr.msf.minute = buffer[9];
				tocentry->cdte_addr.msf.second = buffer[10];
				tocentry->cdte_addr.msf.frame = buffer[11];
			} else
				tocentry->cdte_addr.lba =
				    (((((buffer[8] << 8) + buffer[9]) << 8)
				      + buffer[10]) << 8) + buffer[11];

			return r ? -EIO : 0;
		}

	default:

		return -ENOSYS;
	}
}
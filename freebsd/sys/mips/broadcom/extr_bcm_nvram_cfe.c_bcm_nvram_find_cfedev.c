#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t u_int ;
struct bcm_nvram_iocfe {int /*<<< orphan*/  io; } ;
typedef  int /*<<< orphan*/  bhnd_nvram_data_class ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_ERR (char*,char*,int) ; 
 int CFE_ERR_DEVNOTFOUND ; 
 int ENODEV ; 
 int bcm_nvram_iocfe_init (struct bcm_nvram_iocfe*,char*) ; 
 int bhnd_nvram_data_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhnd_nvram_io_free (int /*<<< orphan*/ *) ; 
 int cfe_getdevinfo (char*) ; 
 size_t nitems (void**) ; 
 void** nvram_cfe_devs ; 
 void** nvram_cfe_fmts ; 

int
bcm_nvram_find_cfedev(struct bcm_nvram_iocfe *iocfe,
    bhnd_nvram_data_class **cls)
{
	char	*dname;
	int	 devinfo;
	int	 error, result;

	for (u_int i = 0; i < nitems(nvram_cfe_fmts); i++) {
		*cls = nvram_cfe_fmts[i];

		for (u_int j = 0; j < nitems(nvram_cfe_devs); j++) {
			dname = nvram_cfe_devs[j];

			/* Does the device exist? */
			if ((devinfo = cfe_getdevinfo(dname)) < 0) {
				if (devinfo != CFE_ERR_DEVNOTFOUND) {
					BCM_ERR("cfe_getdevinfo(%s) failed: "
					    "%d\n", dname, devinfo);
				}

				continue;
			}

			/* Open for reading */
			if ((error = bcm_nvram_iocfe_init(iocfe, dname)))
				continue;

			/* Probe */
			result = bhnd_nvram_data_probe(*cls, &iocfe->io);
			if (result <= 0) {
				/* Found a supporting NVRAM data class */
				return (0);
			}

			/* Keep searching */
			bhnd_nvram_io_free(&iocfe->io);
		}
	}

	return (ENODEV);
}
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
struct pg {int present; int /*<<< orphan*/  pi; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 size_t D_DLY ; 
 size_t D_MOD ; 
 size_t D_PRO ; 
 size_t D_PRT ; 
 size_t D_UNI ; 
 int PG_UNITS ; 
 int /*<<< orphan*/  PG_VERSION ; 
 int /*<<< orphan*/  PI_PG ; 
 struct pg* devices ; 
 int*** drives ; 
 int /*<<< orphan*/  major ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  par_drv ; 
 scalar_t__ pg_drive_count ; 
 int /*<<< orphan*/  pg_probe (struct pg*) ; 
 int /*<<< orphan*/  pg_scratch ; 
 scalar_t__ pi_init (int /*<<< orphan*/ ,int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pi_register_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pi_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pi_unregister_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int pg_detect(void)
{
	struct pg *dev = &devices[0];
	int k, unit;

	printk("%s: %s version %s, major %d\n", name, name, PG_VERSION, major);

	par_drv = pi_register_driver(name);
	if (!par_drv) {
		pr_err("failed to register %s driver\n", name);
		return -1;
	}

	k = 0;
	if (pg_drive_count == 0) {
		if (pi_init(dev->pi, 1, -1, -1, -1, -1, -1, pg_scratch,
			    PI_PG, verbose, dev->name)) {
			if (!pg_probe(dev)) {
				dev->present = 1;
				k++;
			} else
				pi_release(dev->pi);
		}

	} else
		for (unit = 0; unit < PG_UNITS; unit++, dev++) {
			int *parm = *drives[unit];
			if (!parm[D_PRT])
				continue;
			if (pi_init(dev->pi, 0, parm[D_PRT], parm[D_MOD],
				    parm[D_UNI], parm[D_PRO], parm[D_DLY],
				    pg_scratch, PI_PG, verbose, dev->name)) {
				if (!pg_probe(dev)) {
					dev->present = 1;
					k++;
				} else
					pi_release(dev->pi);
			}
		}

	if (k)
		return 0;

	pi_unregister_driver(par_drv);
	printk("%s: No ATAPI device detected\n", name);
	return -1;
}
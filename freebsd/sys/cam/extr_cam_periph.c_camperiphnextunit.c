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
typedef  int u_int ;
typedef  int /*<<< orphan*/  target_id_t ;
struct periph_driver {char* driver_name; int /*<<< orphan*/  units; } ;
struct cam_periph {int unit_number; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  path_id_t ;
typedef  int /*<<< orphan*/  lun_id_t ;

/* Variables and functions */
 struct cam_periph* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct cam_periph* TAILQ_NEXT (struct cam_periph*,int /*<<< orphan*/ ) ; 
 int resource_find_dev (int*,char const*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ resource_int_value (char const*,int,char*,int*) ; 
 scalar_t__ resource_string_value (char const*,int,char*,char const**) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  unit_links ; 
 int /*<<< orphan*/  xpt_print (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static u_int
camperiphnextunit(struct periph_driver *p_drv, u_int newunit, int wired,
		  path_id_t pathid, target_id_t target, lun_id_t lun)
{
	struct	cam_periph *periph;
	char	*periph_name;
	int	i, val, dunit, r;
	const char *dname, *strval;

	periph_name = p_drv->driver_name;
	for (;;newunit++) {

		for (periph = TAILQ_FIRST(&p_drv->units);
		     periph != NULL && periph->unit_number != newunit;
		     periph = TAILQ_NEXT(periph, unit_links))
			;

		if (periph != NULL && periph->unit_number == newunit) {
			if (wired != 0) {
				xpt_print(periph->path, "Duplicate Wired "
				    "Device entry!\n");
				xpt_print(periph->path, "Second device (%s "
				    "device at scbus%d target %d lun %d) will "
				    "not be wired\n", periph_name, pathid,
				    target, lun);
				wired = 0;
			}
			continue;
		}
		if (wired)
			break;

		/*
		 * Don't match entries like "da 4" as a wired down
		 * device, but do match entries like "da 4 target 5"
		 * or even "da 4 scbus 1". 
		 */
		i = 0;
		dname = periph_name;
		for (;;) {
			r = resource_find_dev(&i, dname, &dunit, NULL, NULL);
			if (r != 0)
				break;
			/* if no "target" and no specific scbus, skip */
			if (resource_int_value(dname, dunit, "target", &val) &&
			    (resource_string_value(dname, dunit, "at",&strval)||
			     strcmp(strval, "scbus") == 0))
				continue;
			if (newunit == dunit)
				break;
		}
		if (r != 0)
			break;
	}
	return (newunit);
}
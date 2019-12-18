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
struct cam_periph {int /*<<< orphan*/  periph_name; } ;
struct cam_ed {int /*<<< orphan*/  periphs; } ;

/* Variables and functions */
 struct cam_periph* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 struct cam_periph* SLIST_NEXT (struct cam_periph*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  periph_links ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xpt_announce_periph (struct cam_periph*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xptpassannouncefunc(struct cam_ed *device, void *arg)
{
	struct cam_periph *periph;
	int i;

	for (periph = SLIST_FIRST(&device->periphs), i = 0; periph != NULL;
	     periph = SLIST_NEXT(periph, periph_links), i++);

	periph = SLIST_FIRST(&device->periphs);
	if ((i == 1)
	 && (strncmp(periph->periph_name, "pass", 4) == 0))
		xpt_announce_periph(periph, NULL);

	return(1);
}
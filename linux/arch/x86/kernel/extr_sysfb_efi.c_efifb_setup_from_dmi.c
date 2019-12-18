#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct screen_info {scalar_t__ lfb_base; int /*<<< orphan*/  lfb_height; int /*<<< orphan*/  lfb_width; int /*<<< orphan*/  lfb_linelength; } ;
struct TYPE_2__ {scalar_t__ base; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  stride; int /*<<< orphan*/  optname; } ;

/* Variables and functions */
 int M_UNKNOWN ; 
 TYPE_1__* efifb_dmi_list ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

void efifb_setup_from_dmi(struct screen_info *si, const char *opt)
{
	int i;

	for (i = 0; i < M_UNKNOWN; i++) {
		if (efifb_dmi_list[i].base != 0 &&
		    !strcmp(opt, efifb_dmi_list[i].optname)) {
			si->lfb_base = efifb_dmi_list[i].base;
			si->lfb_linelength = efifb_dmi_list[i].stride;
			si->lfb_width = efifb_dmi_list[i].width;
			si->lfb_height = efifb_dmi_list[i].height;
		}
	}
}
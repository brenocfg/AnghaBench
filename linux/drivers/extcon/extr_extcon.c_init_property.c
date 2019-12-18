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
struct extcon_dev {struct extcon_cable* cables; } ;
struct extcon_cable {int /*<<< orphan*/  disp_propval; int /*<<< orphan*/  jack_propval; int /*<<< orphan*/  chg_propval; int /*<<< orphan*/  usb_propval; } ;
struct TYPE_2__ {unsigned int type; } ;

/* Variables and functions */
 unsigned int EXTCON_TYPE_CHG ; 
 unsigned int EXTCON_TYPE_DISP ; 
 unsigned int EXTCON_TYPE_JACK ; 
 unsigned int EXTCON_TYPE_USB ; 
 TYPE_1__* extcon_info ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_property(struct extcon_dev *edev, unsigned int id, int index)
{
	unsigned int type = extcon_info[id].type;
	struct extcon_cable *cable = &edev->cables[index];

	if (EXTCON_TYPE_USB & type)
		memset(cable->usb_propval, 0, sizeof(cable->usb_propval));
	if (EXTCON_TYPE_CHG & type)
		memset(cable->chg_propval, 0, sizeof(cable->chg_propval));
	if (EXTCON_TYPE_JACK & type)
		memset(cable->jack_propval, 0, sizeof(cable->jack_propval));
	if (EXTCON_TYPE_DISP & type)
		memset(cable->disp_propval, 0, sizeof(cable->disp_propval));
}
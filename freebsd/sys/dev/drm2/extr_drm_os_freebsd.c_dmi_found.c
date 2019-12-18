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
struct dmi_system_id {TYPE_1__* matches; } ;
struct TYPE_2__ {int slot; int /*<<< orphan*/  substr; } ;

/* Variables and functions */
#define  DMI_BOARD_NAME 132 
#define  DMI_BOARD_VENDOR 131 
#define  DMI_NONE 130 
#define  DMI_PRODUCT_NAME 129 
#define  DMI_SYS_VENDOR 128 
 int /*<<< orphan*/  freeenv (char*) ; 
 char* kern_getenv (char*) ; 
 int nitems (TYPE_1__*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
dmi_found(const struct dmi_system_id *dsi)
{
	char *hw_vendor, *hw_prod;
	int i, slot;
	bool res;

	hw_vendor = kern_getenv("smbios.planar.maker");
	hw_prod = kern_getenv("smbios.planar.product");
	res = true;
	for (i = 0; i < nitems(dsi->matches); i++) {
		slot = dsi->matches[i].slot;
		switch (slot) {
		case DMI_NONE:
			break;
		case DMI_SYS_VENDOR:
		case DMI_BOARD_VENDOR:
			if (hw_vendor != NULL &&
			    !strcmp(hw_vendor, dsi->matches[i].substr)) {
				break;
			} else {
				res = false;
				goto out;
			}
		case DMI_PRODUCT_NAME:
		case DMI_BOARD_NAME:
			if (hw_prod != NULL &&
			    !strcmp(hw_prod, dsi->matches[i].substr)) {
				break;
			} else {
				res = false;
				goto out;
			}
		default:
			res = false;
			goto out;
		}
	}
out:
	freeenv(hw_vendor);
	freeenv(hw_prod);

	return (res);
}
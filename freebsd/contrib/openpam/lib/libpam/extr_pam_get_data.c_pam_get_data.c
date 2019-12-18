#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* module_data; } ;
typedef  TYPE_1__ pam_handle_t ;
struct TYPE_5__ {scalar_t__ data; int /*<<< orphan*/  name; struct TYPE_5__* next; } ;
typedef  TYPE_2__ pam_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENTERS (char const*) ; 
 int /*<<< orphan*/  PAM_NO_MODULE_DATA ; 
 int /*<<< orphan*/  PAM_SUCCESS ; 
 int /*<<< orphan*/  RETURNC (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

int
pam_get_data(const pam_handle_t *pamh,
	const char *module_data_name,
	const void **data)
{
	pam_data_t *dp;

	ENTERS(module_data_name);
	for (dp = pamh->module_data; dp != NULL; dp = dp->next) {
		if (strcmp(dp->name, module_data_name) == 0) {
			*data = (void *)dp->data;
			RETURNC(PAM_SUCCESS);
		}
	}
	RETURNC(PAM_NO_MODULE_DATA);
}
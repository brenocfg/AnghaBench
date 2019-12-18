#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* module_data; } ;
typedef  TYPE_1__ pam_handle_t ;
struct TYPE_10__ {void (* cleanup ) (TYPE_1__*,void*,int) ;void* data; struct TYPE_10__* next; int /*<<< orphan*/ * name; } ;
typedef  TYPE_3__ pam_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENTERS (char const*) ; 
 int /*<<< orphan*/  FREE (TYPE_3__*) ; 
 int PAM_BUF_ERR ; 
 int PAM_SUCCESS ; 
 int /*<<< orphan*/  RETURNC (int) ; 
 TYPE_3__* malloc (int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 void stub1 (TYPE_1__*,void*,int) ; 

int
pam_set_data(pam_handle_t *pamh,
	const char *module_data_name,
	void *data,
	void (*cleanup)(pam_handle_t *pamh,
		void *data,
		int pam_end_status))
{
	pam_data_t *dp;

	ENTERS(module_data_name);
	for (dp = pamh->module_data; dp != NULL; dp = dp->next) {
		if (strcmp(dp->name, module_data_name) == 0) {
			if (dp->cleanup)
				(dp->cleanup)(pamh, dp->data, PAM_SUCCESS);
			dp->data = data;
			dp->cleanup = cleanup;
			RETURNC(PAM_SUCCESS);
		}
	}
	if ((dp = malloc(sizeof *dp)) == NULL)
		RETURNC(PAM_BUF_ERR);
	if ((dp->name = strdup(module_data_name)) == NULL) {
		FREE(dp);
		RETURNC(PAM_BUF_ERR);
	}
	dp->data = data;
	dp->cleanup = cleanup;
	dp->next = pamh->module_data;
	pamh->module_data = dp;
	RETURNC(PAM_SUCCESS);
}
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
struct tac_handle {int dummy; } ;
typedef  int (* set_func ) (struct tac_handle*,char const*) ;
typedef  int /*<<< orphan*/  pam_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_CRIT ; 
 int PAM_SERVICE_ERR ; 
 int PAM_SUCCESS ; 
 int pam_get_item (int /*<<< orphan*/ *,int,void const**) ; 
 int stub1 (struct tac_handle*,char const*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tac_close (struct tac_handle*) ; 
 int /*<<< orphan*/  tac_strerror (struct tac_handle*) ; 

__attribute__((used)) static int
do_item(pam_handle_t *pamh, struct tac_handle *tach, int item,
    set_func func, const char *funcname)
{
	int retval;
	const void *value;

	retval = pam_get_item(pamh, item, &value);
	if (retval != PAM_SUCCESS)
	    return retval;
	if (value != NULL && (*func)(tach, (const char *)value) == -1) {
		syslog(LOG_CRIT, "%s: %s", funcname, tac_strerror(tach));
		tac_close(tach);
		return PAM_SERVICE_ERR;
	}
	return PAM_SUCCESS;
}
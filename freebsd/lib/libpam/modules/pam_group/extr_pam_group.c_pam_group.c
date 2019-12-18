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
struct passwd {scalar_t__ pw_uid; scalar_t__ pw_gid; int /*<<< orphan*/  pw_name; } ;
struct group {char** gr_mem; scalar_t__ gr_gid; } ;
typedef  int /*<<< orphan*/  pam_handle_t ;

/* Variables and functions */
 int PAM_AUTH_ERR ; 
 int PAM_IGNORE ; 
 int /*<<< orphan*/  PAM_LOG_ERROR ; 
 int /*<<< orphan*/  PAM_LOG_NOTICE ; 
 int /*<<< orphan*/  PAM_RUSER ; 
 int PAM_SERVICE_ERR ; 
 scalar_t__ PAM_SUCCESS ; 
 struct group* getgrnam (char const*) ; 
 struct passwd* getpwnam (void const*) ; 
 char* openpam_get_option (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  openpam_log (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pam_get_item (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const**) ; 
 scalar_t__ pam_get_user (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pam_group(pam_handle_t *pamh)
{
	int local, remote;
	const char *group, *user;
	const void *ruser;
	char *const *list;
	struct passwd *pwd;
	struct group *grp;

	/* get target account */
	if (pam_get_user(pamh, &user, NULL) != PAM_SUCCESS ||
	    user == NULL || (pwd = getpwnam(user)) == NULL)
		return (PAM_AUTH_ERR);
	if (pwd->pw_uid != 0 && openpam_get_option(pamh, "root_only"))
		return (PAM_IGNORE);

	/* check local / remote */
	local = openpam_get_option(pamh, "luser") ? 1 : 0;
	remote = openpam_get_option(pamh, "ruser") ? 1 : 0;
	if (local && remote) {
		openpam_log(PAM_LOG_ERROR, "(pam_group) "
		    "the luser and ruser options are mutually exclusive");
		return (PAM_SERVICE_ERR);
	} else if (local) {
		/* we already have the correct struct passwd */
	} else {
		if (!remote)
			openpam_log(PAM_LOG_NOTICE, "(pam_group) "
			    "neither luser nor ruser specified, assuming ruser");
		/* default / historical behavior */
		if (pam_get_item(pamh, PAM_RUSER, &ruser) != PAM_SUCCESS ||
		    ruser == NULL || (pwd = getpwnam(ruser)) == NULL)
			return (PAM_AUTH_ERR);
	}

	/* get regulating group */
	if ((group = openpam_get_option(pamh, "group")) == NULL)
		group = "wheel";
	if ((grp = getgrnam(group)) == NULL || grp->gr_mem == NULL)
		goto failed;

	/* check if user's own primary group */
	if (pwd->pw_gid == grp->gr_gid)
		goto found;

	/* iterate over members */
	for (list = grp->gr_mem; list != NULL && *list != NULL; ++list)
		if (strcmp(*list, pwd->pw_name) == 0)
			goto found;

 not_found:
	if (openpam_get_option(pamh, "deny"))
		return (PAM_SUCCESS);
	return (PAM_AUTH_ERR);
 found:
	if (openpam_get_option(pamh, "deny"))
		return (PAM_AUTH_ERR);
	return (PAM_SUCCESS);
 failed:
	if (openpam_get_option(pamh, "fail_safe"))
		goto found;
	else
		goto not_found;
}
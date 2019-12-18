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
typedef  scalar_t__ uid_t ;
typedef  int /*<<< orphan*/ * krb5_principal ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;

/* Variables and functions */
 int /*<<< orphan*/  KRB5_DEFAULT_CCROOT ; 
 int /*<<< orphan*/  PAM_LOG (char*,...) ; 
 int /*<<< orphan*/  asprintf (char**,char*,char*,unsigned long,...) ; 
 long errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 scalar_t__ geteuid () ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  krb5_cc_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long krb5_cc_get_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 long krb5_cc_resolve (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_error_message (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* krb5_get_error_message (int /*<<< orphan*/ ,long) ; 
 long krb5_make_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 long krb5_parse_name (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 long krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char**) ; 
 long seteuid (scalar_t__) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 char* strdup (char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  superuser ; 

__attribute__((used)) static long
get_su_principal(krb5_context context, const char *target_user, const char *current_user,
    char **su_principal_name, krb5_principal *su_principal)
{
	krb5_principal	 default_principal;
	krb5_ccache	 ccache;
	char		*principal_name, *ccname, *p;
	long		 rv;
	uid_t		 euid, ruid;

	*su_principal = NULL;
	default_principal = NULL;
	/* Unless KRB5CCNAME was explicitly set, we won't really be able
	 * to look at the credentials cache since krb5_cc_default will
	 * look at getuid().
	 */
	ruid = getuid();
	euid = geteuid();
	rv = seteuid(ruid);
	if (rv != 0)
		return (errno);
	p = getenv("KRB5CCNAME");
	if (p != NULL)
		ccname = strdup(p);
	else
		(void)asprintf(&ccname, "%s%lu", KRB5_DEFAULT_CCROOT, (unsigned long)ruid);
	if (ccname == NULL)
		return (errno);
	rv = krb5_cc_resolve(context, ccname, &ccache);
	free(ccname);
	if (rv == 0) {
		rv = krb5_cc_get_principal(context, ccache, &default_principal);
		krb5_cc_close(context, ccache);
		if (rv != 0)
			default_principal = NULL; /* just to be safe */
	}
	rv = seteuid(euid);
	if (rv != 0)
		return (errno);
	if (default_principal == NULL) {
		rv = krb5_make_principal(context, &default_principal, NULL, current_user, NULL);
		if (rv != 0) {
			PAM_LOG("Could not determine default principal name.");
			return (rv);
		}
	}
	/* Now that we have some principal, if the target account is
	 * `root', then transform it into a `root' instance, e.g.
	 * `user@REA.LM' -> `user/root@REA.LM'.
	 */
	rv = krb5_unparse_name(context, default_principal, &principal_name);
	krb5_free_principal(context, default_principal);
	if (rv != 0) {
		const char *msg = krb5_get_error_message(context, rv);
		PAM_LOG("krb5_unparse_name: %s", msg);
		krb5_free_error_message(context, msg);
		return (rv);
	}
	PAM_LOG("Default principal name: %s", principal_name);
	if (strcmp(target_user, superuser) == 0) {
		p = strrchr(principal_name, '@');
		if (p == NULL) {
			PAM_LOG("malformed principal name `%s'", principal_name);
			free(principal_name);
			return (rv);
		}
		*p++ = '\0';
		*su_principal_name = NULL;
		(void)asprintf(su_principal_name, "%s/%s@%s", principal_name, superuser, p);
		free(principal_name);
	} else
		*su_principal_name = principal_name;

	if (*su_principal_name == NULL)
		return (errno);
	rv = krb5_parse_name(context, *su_principal_name, &default_principal);
	if (rv != 0) {
		const char *msg = krb5_get_error_message(context, rv);
		PAM_LOG("krb5_parse_name `%s': %s", *su_principal_name, msg);
		krb5_free_error_message(context, msg);
		free(*su_principal_name);
		return (rv);
	}
	PAM_LOG("Target principal name: %s", *su_principal_name);
	*su_principal = default_principal;
	return (0);
}
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
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  kadm5_principal_ent_rec ;

/* Variables and functions */
 int /*<<< orphan*/  KRB5_TGS_NAME ; 
 int asprintf (char**,char*,char*,...) ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  do_check_entry ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  foreach_principal (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_check_entry (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kadm5_free_principal_ent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kadm_handle ; 
 scalar_t__ krb5_get_default_realm (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strlwr (char*) ; 

int
check(void *opt, int argc, char **argv)
{
    kadm5_principal_ent_rec ent;
    krb5_error_code ret;
    char *realm = NULL, *p, *p2;
    int found;

    if (argc == 0) {
	ret = krb5_get_default_realm(context, &realm);
	if (ret) {
	    krb5_warn(context, ret, "krb5_get_default_realm");
	    goto fail;
	}
    } else {
	realm = strdup(argv[0]);
	if (realm == NULL) {
	    krb5_warnx(context, "malloc");
	    goto fail;
	}
    }

    /*
     * Check krbtgt/REALM@REALM
     *
     * For now, just check existance
     */

    if (asprintf(&p, "%s/%s@%s", KRB5_TGS_NAME, realm, realm) == -1) {
	krb5_warn(context, errno, "asprintf");
	goto fail;
    }

    ret = get_check_entry(p, &ent);
    if (ret) {
	printf("%s doesn't exist, are you sure %s is a realm in your database",
	       p, realm);
	free(p);
	goto fail;
    }
    free(p);

    kadm5_free_principal_ent(kadm_handle, &ent);

    /*
     * Check kadmin/admin@REALM
     */

    if (asprintf(&p, "kadmin/admin@%s", realm) == -1) {
	krb5_warn(context, errno, "asprintf");
	goto fail;
    }

    ret = get_check_entry(p, &ent);
    if (ret) {
	printf("%s doesn't exist, "
	       "there is no way to do remote administration", p);
	free(p);
	goto fail;
    }
    free(p);

    kadm5_free_principal_ent(kadm_handle, &ent);

    /*
     * Check kadmin/changepw@REALM
     */

    if (asprintf(&p, "kadmin/changepw@%s", realm) == -1) {
	krb5_warn(context, errno, "asprintf");
	goto fail;
    }

    ret = get_check_entry(p, &ent);
    if (ret) {
	printf("%s doesn't exist, "
	       "there is no way to do change password", p);
	free(p);
	goto fail;
    }
    free(p);

    kadm5_free_principal_ent(kadm_handle, &ent);

    /*
     * Check for duplicate afs keys
     */

    p2 = strdup(realm);
    if (p2 == NULL) {
	krb5_warn(context, errno, "malloc");
	goto fail;
    }
    strlwr(p2);

    if (asprintf(&p, "afs/%s@%s", p2, realm) == -1) {
	krb5_warn(context, errno, "asprintf");
	free(p2);
	goto fail;
    }
    free(p2);

    ret = get_check_entry(p, &ent);
    free(p);
    if (ret == 0) {
	kadm5_free_principal_ent(kadm_handle, &ent);
	found = 1;
    } else
	found = 0;

    if (asprintf(&p, "afs@%s", realm) == -1) {
	krb5_warn(context, errno, "asprintf");
	goto fail;
    }

    ret = get_check_entry(p, &ent);
    free(p);
    if (ret == 0) {
	kadm5_free_principal_ent(kadm_handle, &ent);
	if (found) {
	    krb5_warnx(context, "afs@REALM and afs/cellname@REALM both exists");
	    goto fail;
	}
    }

    foreach_principal("*", do_check_entry, "check", NULL);

    free(realm);
    return 0;
fail:
    free(realm);
    return 1;
}
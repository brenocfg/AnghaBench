#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
typedef  scalar_t__ time_t ;
struct passwd {char* pw_name; } ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_5__ {scalar_t__ endtime; } ;
struct TYPE_6__ {TYPE_1__ times; int /*<<< orphan*/  client; int /*<<< orphan*/  server; } ;
typedef  TYPE_2__ krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;
typedef  int /*<<< orphan*/  krb5_cc_cursor ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_cc_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_cc_end_seq_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_next_cred (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ krb5_cc_resolve (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_start_seq_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_free_cred_contents (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ krb5_init_context (int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 char* pref_realm ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
is_a_valid_tgt_cache(const char *filepath, uid_t uid, int *retrating,
    time_t *retexptime)
{
#ifndef WITHOUT_KERBEROS
	krb5_context context;
	krb5_principal princ;
	krb5_ccache ccache;
	krb5_error_code retval;
	krb5_cc_cursor curse;
	krb5_creds krbcred;
	int gotone, orating, rating, ret;
	struct passwd *pw;
	char *cp, *cp2, *pname;
	time_t exptime;

	/* Find a likely name for the uid principal. */
	pw = getpwuid(uid);

	/*
	 * Do a bunch of krb5 library stuff to try and determine if
	 * this file is a credentials cache with an appropriate TGT
	 * in it.
	 */
	retval = krb5_init_context(&context);
	if (retval != 0)
		return (0);
	retval = krb5_cc_resolve(context, filepath, &ccache);
	if (retval != 0) {
		krb5_free_context(context);
		return (0);
	}
	ret = 0;
	orating = 0;
	exptime = 0;
	retval = krb5_cc_start_seq_get(context, ccache, &curse);
	if (retval == 0) {
		while ((retval = krb5_cc_next_cred(context, ccache, &curse,
		    &krbcred)) == 0) {
			gotone = 0;
			rating = 0;
			retval = krb5_unparse_name(context, krbcred.server,
			    &pname);
			if (retval == 0) {
				cp = strchr(pname, '/');
				if (cp != NULL) {
					*cp++ = '\0';
					if (strcmp(pname, "krbtgt") == 0 &&
					    krbcred.times.endtime > time(NULL)
					    ) {
						gotone = 1;
						/*
						 * Test to see if this is a
						 * tgt for cross-realm auth.
						 * Rate it higher, if it is not.
						 */
						cp2 = strchr(cp, '@');
						if (cp2 != NULL) {
							*cp2++ = '\0';
							if (strcmp(cp, cp2) ==
							    0)
								rating++;
						}
					}
				}
				free(pname);
			}
			if (gotone != 0) {
				retval = krb5_unparse_name(context,
				    krbcred.client, &pname);
				if (retval == 0) {
					cp = strchr(pname, '@');
					if (cp != NULL) {
						*cp++ = '\0';
						if (pw != NULL && strcmp(pname,
						    pw->pw_name) == 0)
							rating++;
						if (strchr(pname, '/') == NULL)
							rating++;
						if (pref_realm[0] != '\0' &&
						    strcmp(cp, pref_realm) == 0)
							rating++;
					}
				}
				free(pname);
				if (rating > orating) {
					orating = rating;
					exptime = krbcred.times.endtime;
				} else if (rating == orating &&
				    krbcred.times.endtime > exptime)
					exptime = krbcred.times.endtime;
				ret = 1;
			}
			krb5_free_cred_contents(context, &krbcred);
		}
		krb5_cc_end_seq_get(context, ccache, &curse);
	}
	krb5_cc_close(context, ccache);
	krb5_free_context(context);
	if (ret != 0) {
		*retrating = orating;
		*retexptime = exptime;
	}
	return (ret);
#else /* WITHOUT_KERBEROS */
	return (0);
#endif /* !WITHOUT_KERBEROS */
}
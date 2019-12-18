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
struct passwd {char* pw_name; } ;
typedef  int /*<<< orphan*/ * krb5_principal ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTTY ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 char* get_env_user () ; 
 char* getlogin () ; 
 struct passwd* getpwuid (scalar_t__) ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  krb5_make_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,char*,...) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

krb5_error_code
_krb5_get_default_principal_local (krb5_context context,
				   krb5_principal *princ)
{
    krb5_error_code ret;
    const char *user;
    uid_t uid;

    *princ = NULL;

    uid = getuid();
    if(uid == 0) {
	user = getlogin();
	if(user == NULL)
	    user = get_env_user();
	if(user != NULL && strcmp(user, "root") != 0)
	    ret = krb5_make_principal(context, princ, NULL, user, "root", NULL);
	else
	    ret = krb5_make_principal(context, princ, NULL, "root", NULL);
    } else {
	struct passwd *pw = getpwuid(uid);
	if(pw != NULL)
	    user = pw->pw_name;
	else {
	    user = get_env_user();
	    if(user == NULL)
		user = getlogin();
	}
	if(user == NULL) {
	    krb5_set_error_message(context, ENOTTY,
				   N_("unable to figure out current "
				      "principal", ""));
	    return ENOTTY; /* XXX */
	}
	ret = krb5_make_principal(context, princ, NULL, user, NULL);
    }
    return ret;
}
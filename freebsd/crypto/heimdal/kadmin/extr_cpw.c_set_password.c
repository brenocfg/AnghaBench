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
typedef  int /*<<< orphan*/  pwbuf ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;

/* Variables and functions */
 scalar_t__ UI_UTIL_read_pw_string (char*,int,char*,int) ; 
 int /*<<< orphan*/  asprintf (char**,char*,char*) ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ kadm5_chpass_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kadm_handle ; 
 int /*<<< orphan*/  krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
set_password (krb5_principal principal, char *password)
{
    krb5_error_code ret = 0;
    char pwbuf[128];

    if(password == NULL) {
	char *princ_name;
	char *prompt;

	krb5_unparse_name(context, principal, &princ_name);
	asprintf(&prompt, "%s's Password: ", princ_name);
	free (princ_name);
	ret = UI_UTIL_read_pw_string(pwbuf, sizeof(pwbuf), prompt, 1);
	free (prompt);
	if(ret){
	    return 0; /* XXX error code? */
	}
	password = pwbuf;
    }
    if(ret == 0)
	ret = kadm5_chpass_principal(kadm_handle, principal, password);
    memset(pwbuf, 0, sizeof(pwbuf));
    return ret;
}
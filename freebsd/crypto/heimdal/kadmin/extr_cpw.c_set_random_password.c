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
typedef  int /*<<< orphan*/  pw ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;

/* Variables and functions */
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ kadm5_chpass_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kadm_handle ; 
 int /*<<< orphan*/  krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  random_password (char*,int) ; 

__attribute__((used)) static int
set_random_password (krb5_principal principal)
{
    krb5_error_code ret;
    char pw[128];

    random_password (pw, sizeof(pw));
    ret = kadm5_chpass_principal(kadm_handle, principal, pw);
    if (ret == 0) {
	char *princ_name;

	krb5_unparse_name(context, principal, &princ_name);

	printf ("%s's password set to \"%s\"\n", princ_name, pw);
	free (princ_name);
    }
    memset (pw, 0, sizeof(pw));
    return ret;
}
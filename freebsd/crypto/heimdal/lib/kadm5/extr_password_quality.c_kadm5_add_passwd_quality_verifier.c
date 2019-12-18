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
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 scalar_t__ add_verifier (int /*<<< orphan*/ ,char const*) ; 
 char** krb5_config_get_strings (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 

krb5_error_code
kadm5_add_passwd_quality_verifier(krb5_context context,
				  const char *check_library)
{
#ifdef HAVE_DLOPEN

    if(check_library == NULL) {
	krb5_error_code ret;
	char **tmp;

	tmp = krb5_config_get_strings(context, NULL,
				      "password_quality",
				      "policy_libraries",
				      NULL);
	if(tmp == NULL || *tmp == NULL)
	    return 0;

	while (*tmp) {
	    ret = add_verifier(context, *tmp);
	    if (ret)
		return ret;
	    tmp++;
	}
	return 0;
    } else {
	return add_verifier(context, check_library);
    }
#else
    return 0;
#endif /* HAVE_DLOPEN */
}
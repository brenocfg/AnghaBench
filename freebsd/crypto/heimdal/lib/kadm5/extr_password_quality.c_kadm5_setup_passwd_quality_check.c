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
typedef  int /*<<< orphan*/  krb5_context ;
typedef  scalar_t__ kadm5_passwd_quality_check_func_v0 ;

/* Variables and functions */
 int KADM5_PASSWD_VERSION_V0 ; 
 int /*<<< orphan*/  RTLD_NOW ; 
 int /*<<< orphan*/  dlclose (void*) ; 
 void* dlopen (char const*,int /*<<< orphan*/ ) ; 
 void* dlsym (void*,char const*) ; 
 char* krb5_config_get_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ passwd_quality_check ; 

void
kadm5_setup_passwd_quality_check(krb5_context context,
				 const char *check_library,
				 const char *check_function)
{
#ifdef HAVE_DLOPEN
    void *handle;
    void *sym;
    int *version;
    const char *tmp;

    if(check_library == NULL) {
	tmp = krb5_config_get_string(context, NULL,
				     "password_quality",
				     "check_library",
				     NULL);
	if(tmp != NULL)
	    check_library = tmp;
    }
    if(check_function == NULL) {
	tmp = krb5_config_get_string(context, NULL,
				     "password_quality",
				     "check_function",
				     NULL);
	if(tmp != NULL)
	    check_function = tmp;
    }
    if(check_library != NULL && check_function == NULL)
	check_function = "passwd_check";

    if(check_library == NULL)
	return;
    handle = dlopen(check_library, RTLD_NOW);
    if(handle == NULL) {
	krb5_warnx(context, "failed to open `%s'", check_library);
	return;
    }
    version = (int *) dlsym(handle, "version");
    if(version == NULL) {
	krb5_warnx(context,
		   "didn't find `version' symbol in `%s'", check_library);
	dlclose(handle);
	return;
    }
    if(*version != KADM5_PASSWD_VERSION_V0) {
	krb5_warnx(context,
		   "version of loaded library is %d (expected %d)",
		   *version, KADM5_PASSWD_VERSION_V0);
	dlclose(handle);
	return;
    }
    sym = dlsym(handle, check_function);
    if(sym == NULL) {
	krb5_warnx(context,
		   "didn't find `%s' symbol in `%s'",
		   check_function, check_library);
	dlclose(handle);
	return;
    }
    passwd_quality_check = (kadm5_passwd_quality_check_func_v0) sym;
#endif /* HAVE_DLOPEN */
}
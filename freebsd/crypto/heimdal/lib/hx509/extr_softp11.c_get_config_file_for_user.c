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
struct passwd {char* pw_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIDL_APPDATA ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SHGFP_TYPE_CURRENT ; 
 int /*<<< orphan*/  SHGetFolderPath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asprintf (char**,char*,char*) ; 
 char* getenv (char*) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  issuid () ; 
 char* strdup (char*) ; 

__attribute__((used)) static char *
get_config_file_for_user(void)
{
    char *fn = NULL;

#ifndef _WIN32
    char *home = NULL;

    if (!issuid()) {
        fn = getenv("SOFTPKCS11RC");
        if (fn)
            fn = strdup(fn);
        home = getenv("HOME");
    }
    if (fn == NULL && home == NULL) {
        struct passwd *pw = getpwuid(getuid());
        if(pw != NULL)
            home = pw->pw_dir;
    }
    if (fn == NULL) {
        if (home)
            asprintf(&fn, "%s/.soft-token.rc", home);
        else
            fn = strdup("/etc/soft-token.rc");
    }
#else  /* Windows */

    char appdatafolder[MAX_PATH];

    fn = getenv("SOFTPKCS11RC");

    /* Retrieve the roaming AppData folder for the current user.  The
       current user is the user account represented by the current
       thread token. */

    if (fn == NULL &&
        SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_CURRENT, appdatafolder))) {

        asprintf(&fn, "%s\\.soft-token.rc", appdatafolder);
    }

#endif  /* _WIN32 */

    return fn;
}
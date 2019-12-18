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
struct passwd {char* pw_dir; char* pw_name; } ;
struct login_vars {char const* var; int overwrite; char* def; int /*<<< orphan*/ * tag; } ;
typedef  int /*<<< orphan*/  login_cap_t ;

/* Variables and functions */
 struct login_vars* envars ; 
 int /*<<< orphan*/  free (char*) ; 
 char** login_getcaplist (int /*<<< orphan*/ *,char*,char*) ; 
 char* login_getcapstr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* login_getpath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct login_vars* pathvars ; 
 int /*<<< orphan*/  setenv (char const*,char*,int) ; 
 char* strchr (char const*,char) ; 
 int strlen (char*) ; 
 char* substvar (char const*,struct passwd const*,int,char,int) ; 

void
setclassenvironment(login_cap_t *lc, const struct passwd * pwd, int paths)
{
    struct login_vars	*vars = paths ? pathvars : envars;
    int			hlen = pwd ? strlen(pwd->pw_dir) : 0;
    int			nlen = pwd ? strlen(pwd->pw_name) : 0;
    char pch = 0;

    if (hlen && pwd->pw_dir[hlen-1] != '/')
	++pch;

    while (vars->tag != NULL) {
	const char * var = paths ? login_getpath(lc, vars->tag, NULL)
				 : login_getcapstr(lc, vars->tag, NULL, NULL);

	char * np  = substvar(var, pwd, hlen, pch, nlen);

	if (np != NULL) {
	    setenv(vars->var, np, vars->overwrite);
	    free(np);
	} else if (vars->def != NULL) {
	    setenv(vars->var, vars->def, 0);
	}
	++vars;
    }

    /*
     * If we're not processing paths, then see if there is a setenv list by
     * which the admin and/or user may set an arbitrary set of env vars.
     */
    if (!paths) {
	const char	**set_env = login_getcaplist(lc, "setenv", ",");

	if (set_env != NULL) {
	    while (*set_env != NULL) {
		char	*p = strchr(*set_env, '=');

		if (p != NULL) {  /* Discard invalid entries */
		    char	*np;

		    *p++ = '\0';
		    if ((np = substvar(p, pwd, hlen, pch, nlen)) != NULL) {
			setenv(*set_env, np, 1);
			free(np);
		    }
		}
		++set_env;
	    }
	}
    }
}
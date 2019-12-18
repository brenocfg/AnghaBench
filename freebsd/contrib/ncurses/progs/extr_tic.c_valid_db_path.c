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
typedef  int /*<<< orphan*/  suffix ;
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 char* DBM_SUFFIX ; 
 int /*<<< orphan*/  DEBUG (int,char*) ; 
 int R_OK ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int W_OK ; 
 int X_OK ; 
 int /*<<< orphan*/  _nc_STRCAT (char*,char*,size_t) ; 
 int /*<<< orphan*/  _nc_STRCPY (char*,char const*,size_t) ; 
 unsigned int _nc_pathlast (char*) ; 
 scalar_t__ access (char*,int) ; 
 int /*<<< orphan*/  failed (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *
valid_db_path(const char *nominal)
{
    struct stat sb;
#if USE_HASHED_DB
    char suffix[] = DBM_SUFFIX;
    size_t need = strlen(nominal) + sizeof(suffix);
    char *result = malloc(need);

    if (result == 0)
	failed("valid_db_path");
    _nc_STRCPY(result, nominal, need);
    if (strcmp(result + need - sizeof(suffix), suffix)) {
	_nc_STRCAT(result, suffix, need);
    }
#else
    char *result = strdup(nominal);
#endif

    DEBUG(1, ("** stat(%s)", result));
    if (stat(result, &sb) >= 0) {
#if USE_HASHED_DB
	if (!S_ISREG(sb.st_mode)
	    || access(result, R_OK | W_OK) != 0) {
	    DEBUG(1, ("...not a writable file"));
	    free(result);
	    result = 0;
	}
#else
	if (!S_ISDIR(sb.st_mode)
	    || access(result, R_OK | W_OK | X_OK) != 0) {
	    DEBUG(1, ("...not a writable directory"));
	    free(result);
	    result = 0;
	}
#endif
    } else {
	/* check if parent is directory and is writable */
	unsigned leaf = _nc_pathlast(result);

	DEBUG(1, ("...not found"));
	if (leaf) {
	    char save = result[leaf];
	    result[leaf] = 0;
	    if (stat(result, &sb) >= 0
		&& S_ISDIR(sb.st_mode)
		&& access(result, R_OK | W_OK | X_OK) == 0) {
		result[leaf] = save;
	    } else {
		DEBUG(1, ("...parent directory %s is not writable", result));
		free(result);
		result = 0;
	    }
	} else {
	    DEBUG(1, ("... no parent directory"));
	    free(result);
	    result = 0;
	}
    }
    return result;
}
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
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  AG_PATH_MAX ; 
 int R_OK ; 
 int W_OK ; 
 int X_OK ; 
 scalar_t__ access (char*,int) ; 
 char* canonicalize_pathname (char*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 char* extract_colon_unit (char*,char const*,int*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* make_absolute (char const*,char*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 scalar_t__ strchr (char const*,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static char *
pathfind( char const * path,
          char const * fname,
          char const * mode )
{
    int    p_index   = 0;
    int    mode_bits = 0;
    char * res_path  = NULL;
    char   zPath[ AG_PATH_MAX + 1 ];

    if (strchr( mode, 'r' )) mode_bits |= R_OK;
    if (strchr( mode, 'w' )) mode_bits |= W_OK;
    if (strchr( mode, 'x' )) mode_bits |= X_OK;

    /*
     *  FOR each non-null entry in the colon-separated path, DO ...
     */
    for (;;) {
        DIR  * dirP;
        char * colon_unit = extract_colon_unit( zPath, path, &p_index );

        if (colon_unit == NULL)
            break;

        dirP = opendir( colon_unit );

        /*
         *  IF the directory is inaccessable, THEN next directory
         */
        if (dirP == NULL)
            continue;

        for (;;) {
            struct dirent *entP = readdir( dirP );

            if (entP == (struct dirent *)NULL)
                break;

            /*
             *  IF the file name matches the one we are looking for, ...
             */
            if (strcmp(entP->d_name, fname) == 0) {
                char * abs_name = make_absolute(fname, colon_unit);

                /*
                 *  Make sure we can access it in the way we want
                 */
                if (access(abs_name, mode_bits) >= 0) {
                    /*
                     *  We can, so normalize the name and return it below
                     */
                    res_path = canonicalize_pathname(abs_name);
                }

                free(abs_name);
                break;
            }
        }

        closedir( dirP );

        if (res_path != NULL)
            break;
    }

    return res_path;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  z ;
struct TYPE_4__ {char const* pzRcName; int /*<<< orphan*/  pzProgName; } ;
typedef  TYPE_1__ tOptions ;
struct stat {void* st_mode; } ;

/* Variables and functions */
 scalar_t__ AGALOC (size_t,char*) ; 
 int /*<<< orphan*/  AGFREE (char const*) ; 
 int AG_PATH_MAX ; 
 int /*<<< orphan*/  DIRCH ; 
 scalar_t__ ENOENT ; 
 char NUL ; 
 void* S_IFREG ; 
 scalar_t__ S_ISDIR (void*) ; 
 int /*<<< orphan*/  S_ISREG (void*) ; 
 scalar_t__ errno ; 
 char* find_dir_name (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*,char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int strlen (char const*) ; 
 char* strrchr (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char const*) ; 
 char* zNoStat ; 
 char* zsave_warn ; 

__attribute__((used)) static char const *
find_file_name(tOptions * opts, int * p_free_name)
{
    struct stat stBuf;
    int    free_dir_name = 0;

    char const * pzDir = find_dir_name(opts, &free_dir_name);
    if (pzDir == NULL)
        return NULL;

    /*
     *  See if we can find the specified directory.  We use a once-only loop
     *  structure so we can bail out early.
     */
    if (stat(pzDir, &stBuf) != 0) do {
        char z[AG_PATH_MAX];
        char * dirchp;

        /*
         *  IF we could not, check to see if we got a full
         *  path to a file name that has not been created yet.
         */
        if (errno != ENOENT) {
        bogus_name:
            fprintf(stderr, zsave_warn, opts->pzProgName);
            fprintf(stderr, zNoStat, errno, strerror(errno), pzDir);
            if (free_dir_name)
                AGFREE(pzDir);
            return NULL;
        }

        /*
         *  Strip off the last component, stat the remaining string and
         *  that string must name a directory
         */
        dirchp = strrchr(pzDir, DIRCH);
        if (dirchp == NULL) {
            stBuf.st_mode = S_IFREG;
            break; /* found directory -- viz.,  "." */
        }

        if ((size_t)(dirchp - pzDir) >= sizeof(z))
            goto bogus_name;

        memcpy(z, pzDir, (size_t)(dirchp - pzDir));
        z[dirchp - pzDir] = NUL;

        if ((stat(z, &stBuf) != 0) || ! S_ISDIR(stBuf.st_mode))
            goto bogus_name;
        stBuf.st_mode = S_IFREG; /* file within this directory */
    } while (false);

    /*
     *  IF what we found was a directory,
     *  THEN tack on the config file name
     */
    if (S_ISDIR(stBuf.st_mode)) {
        size_t sz = strlen(pzDir) + strlen(opts->pzRcName) + 2;

        {
            char * pzPath = (char *)AGALOC(sz, "file name");
#ifdef HAVE_SNPRINTF
            snprintf(pzPath, sz, "%s/%s", pzDir, opts->pzRcName);
#else
            sprintf(pzPath, "%s/%s", pzDir, opts->pzRcName);
#endif
            if (free_dir_name)
                AGFREE(pzDir);
            pzDir = pzPath;
            free_dir_name = 1;
        }

        /*
         *  IF we cannot stat the object for any reason other than
         *     it does not exist, then we bail out
         */
        if (stat(pzDir, &stBuf) != 0) {
            if (errno != ENOENT) {
                fprintf(stderr, zsave_warn, opts->pzProgName);
                fprintf(stderr, zNoStat, errno, strerror(errno),
                        pzDir);
                AGFREE(pzDir);
                return NULL;
            }

            /*
             *  It does not exist yet, but it will be a regular file
             */
            stBuf.st_mode = S_IFREG;
        }
    }

    /*
     *  Make sure that whatever we ultimately found, that it either is
     *  or will soon be a file.
     */
    if (! S_ISREG(stBuf.st_mode)) {
        fprintf(stderr, zsave_warn, opts->pzProgName, pzDir);
        if (free_dir_name)
            AGFREE(pzDir);
        return NULL;
    }

    /*
     *  Get rid of the old file
     */
    unlink(pzDir);
    *p_free_name = free_dir_name;
    return pzDir;
}
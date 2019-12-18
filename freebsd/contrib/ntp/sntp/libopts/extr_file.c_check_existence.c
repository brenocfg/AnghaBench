#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int teOptFileType ;
struct TYPE_7__ {int /*<<< orphan*/  pzProgName; } ;
typedef  TYPE_2__ tOptions ;
struct TYPE_6__ {char* argString; } ;
struct TYPE_8__ {TYPE_1__ optArg; } ;
typedef  TYPE_3__ tOptDesc ;
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 char* AGALOC (size_t,char*) ; 
 int /*<<< orphan*/  AGFREE (char*) ; 
 int /*<<< orphan*/  DIRCH ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOENT ; 
 int FTYPE_MODE_EXIST_MASK ; 
#define  FTYPE_MODE_MAY_EXIST 130 
#define  FTYPE_MODE_MUST_EXIST 129 
#define  FTYPE_MODE_MUST_NOT_EXIST 128 
 char NUL ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fserr_exit (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  stat (char const*,struct stat*) ; 
 char* strrchr (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_existence(teOptFileType ftype, tOptions * pOpts, tOptDesc * pOD)
{
    char const * fname = pOD->optArg.argString;
    struct stat sb;

    errno = 0;

    switch (ftype & FTYPE_MODE_EXIST_MASK) {
    case FTYPE_MODE_MUST_NOT_EXIST:
        if ((stat(fname, &sb) == 0) || (errno != ENOENT)) {
            if (errno == 0)
                errno = EINVAL;
            fserr_exit(pOpts->pzProgName, "stat", fname);
            /* NOTREACHED */
        }
        /* FALLTHROUGH */

    default:
    case FTYPE_MODE_MAY_EXIST:
    {
        char * p = strrchr(fname, DIRCH);
        size_t l;

        if (p == NULL)
            /*
             *  The file may or may not exist and its directory is ".".
             *  Assume that "." exists.
             */
            break;

        l = (size_t)(p - fname);
        p = AGALOC(l + 1, "fname");
        memcpy(p, fname, l);
        p[l] = NUL;

        if ((stat(p, &sb) != 0) || (errno = EINVAL, ! S_ISDIR(sb.st_mode)))
            fserr_exit(pOpts->pzProgName, "stat", p);
            /* NOTREACHED */

        AGFREE(p);
        break;
    }

    case FTYPE_MODE_MUST_EXIST:
        if (  (stat(fname, &sb) != 0)
           || (errno = EINVAL, ! S_ISREG(sb.st_mode))  )
            fserr_exit(pOpts->pzProgName, "stat", fname);
            /* NOTREACHED */

        break;
    }
}
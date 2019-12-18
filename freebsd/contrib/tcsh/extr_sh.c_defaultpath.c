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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  DIRAPPEND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRdot ; 
 void* Strsave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _PATH_BIN ; 
 int /*<<< orphan*/  _PATH_LOCAL ; 
 int /*<<< orphan*/  _PATH_USRBIN ; 
 int /*<<< orphan*/  _PATH_USRBSD ; 
 int /*<<< orphan*/  _PATH_USRUCB ; 
 int /*<<< orphan*/ ** xmalloc (int) ; 

__attribute__((used)) static Char **
defaultpath(void)
{
    char   *ptr;
    Char  **blk, **blkp;
    struct stat stb;

    blkp = blk = xmalloc(sizeof(Char *) * 10);

#ifndef NODOT
# ifndef DOTLAST
    *blkp++ = Strsave(STRdot);
# endif
#endif

#define DIRAPPEND(a)  \
	if (stat(ptr = a, &stb) == 0 && S_ISDIR(stb.st_mode)) \
		*blkp++ = SAVE(ptr)

#ifdef _PATH_LOCAL
    DIRAPPEND(_PATH_LOCAL);
#endif

#ifdef _PATH_USRUCB
    DIRAPPEND(_PATH_USRUCB);
#endif

#ifdef _PATH_USRBSD
    DIRAPPEND(_PATH_USRBSD);
#endif

#ifdef _PATH_BIN
    DIRAPPEND(_PATH_BIN);
#endif

#ifdef _PATH_USRBIN
    DIRAPPEND(_PATH_USRBIN);
#endif

#undef DIRAPPEND

#ifndef NODOT
# ifdef DOTLAST
    *blkp++ = Strsave(STRdot);
# endif
#endif
    *blkp = NULL;
    return (blk);
}
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
typedef  int /*<<< orphan*/ * command ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  STRsavehist ; 
 int /*<<< orphan*/  USE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  _PATH_BIN_LOGIN ; 
 int /*<<< orphan*/  _PATH_USRBIN_LOGIN ; 
 int /*<<< orphan*/ * adrof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_cleanup ; 
 int /*<<< orphan*/  cleanup_push (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  execv (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  islogin () ; 
 int /*<<< orphan*/  parterm ; 
 int /*<<< orphan*/  rechist (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char** short2blk (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  untty () ; 
 int /*<<< orphan*/  xexit (int) ; 

void
dologin(Char **v, struct command *c)
{
#ifdef WINNT_NATIVE
    USE(c);
    USE(v);
#else /* !WINNT_NATIVE */
    char **p = short2blk(v);

    USE(c);
    cleanup_push((Char **)p, blk_cleanup);
    islogin();
    rechist(NULL, adrof(STRsavehist) != NULL);
    sigaction(SIGTERM, &parterm, NULL);
    (void) execv(_PATH_BIN_LOGIN, p);
    (void) execv(_PATH_USRBIN_LOGIN, p);
    cleanup_until((Char **)p);
    untty();
    xexit(1);
#endif /* !WINNT_NATIVE */
}
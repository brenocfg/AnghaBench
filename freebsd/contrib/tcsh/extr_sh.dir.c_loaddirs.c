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
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/ * STRNULL ; 
 int /*<<< orphan*/  STRdirsfile ; 
#define  STRsource 128 
 int /*<<< orphan*/ * STRtildotdirs ; 
 int bequiet ; 
 int /*<<< orphan*/  bequiet_cleanup ; 
 int /*<<< orphan*/  cleanup_push (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (int*) ; 
 int /*<<< orphan*/  dosource (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * varval (int /*<<< orphan*/ ) ; 

void
loaddirs(Char *fname)
{
    static Char *loaddirs_cmd[] = { STRsource, NULL, NULL };

    bequiet = 1;
    cleanup_push(&bequiet, bequiet_cleanup);
    if (fname)
	loaddirs_cmd[1] = fname;
    else if ((fname = varval(STRdirsfile)) != STRNULL)
	loaddirs_cmd[1] = fname;
    else
	loaddirs_cmd[1] = STRtildotdirs;
    dosource(loaddirs_cmd, NULL);
    cleanup_until(&bequiet);
}
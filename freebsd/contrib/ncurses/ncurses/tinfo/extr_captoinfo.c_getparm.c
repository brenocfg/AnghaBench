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

/* Variables and functions */
 int /*<<< orphan*/  _nc_warning (char*) ; 
 int /*<<< orphan*/  dp ; 
 int onstack ; 
 int /*<<< orphan*/  push () ; 
 int /*<<< orphan*/  save_char (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  save_string (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ seenm ; 
 scalar_t__ seenn ; 
 scalar_t__ seenr ; 

__attribute__((used)) static void
getparm(int parm, int n)
/* push n copies of param on the terminfo stack if not already there */
{
    if (seenr) {
	if (parm == 1)
	    parm = 2;
	else if (parm == 2)
	    parm = 1;
    }

    while (n--) {
	dp = save_string(dp, "%p");
	dp = save_char(dp, '0' + parm);
    }

    if (onstack == parm) {
	if (n > 1) {
	    _nc_warning("string may not be optimal");
	    dp = save_string(dp, "%Pa");
	    while (n--) {
		dp = save_string(dp, "%ga");
	    }
	}
	return;
    }
    if (onstack != 0)
	push();

    onstack = parm;

    if (seenn && parm < 3) {
	dp = save_string(dp, "%{96}%^");
    }

    if (seenm && parm < 3) {
	dp = save_string(dp, "%{127}%^");
    }
}
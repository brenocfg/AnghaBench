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
struct command {int dummy; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  G_ERROR ; 
 int /*<<< orphan*/  USE (struct command*) ; 
 int /*<<< orphan*/  cleanup_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * globone (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gotolab (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  noexec ; 
 int /*<<< orphan*/  xfree ; 

void
dogoto(Char **v, struct command *c)
{
    Char   *lp;

    USE(c);
    lp = globone(v[1], G_ERROR);
    cleanup_push(lp, xfree);
    if (!noexec)
	gotolab(lp);
    cleanup_until(lp);
}
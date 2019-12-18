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
 int /*<<< orphan*/ * Strsave (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cleanup_ignore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setv (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xfree ; 

void
setcopy(const Char *var, const Char *val, int flags)
{
    Char *copy;

    copy = Strsave(val);
    cleanup_push(copy, xfree);
    setv(var, copy, flags);
    cleanup_ignore(copy);
    cleanup_until(copy);
}
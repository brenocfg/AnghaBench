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
struct varent {int v_flags; int /*<<< orphan*/ ** vec; int /*<<< orphan*/  v_name; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int ERR_NAME ; 
 int ERR_READONLY ; 
 int /*<<< orphan*/  G_APPEND ; 
 int VAR_READONLY ; 
 int /*<<< orphan*/  cleanup_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (int /*<<< orphan*/ *) ; 
 struct varent* getvx (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * globone (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderror (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree ; 

__attribute__((used)) static void
asx(Char *vp, int subscr, Char *p)
{
    struct varent *v = getvx(vp, subscr);
    Char *prev;

    if (v->v_flags & VAR_READONLY)
	stderror(ERR_READONLY|ERR_NAME, v->v_name);
    prev = v->vec[subscr - 1];
    cleanup_push(prev, xfree);
    v->vec[subscr - 1] = globone(p, G_APPEND);
    cleanup_until(prev);
}
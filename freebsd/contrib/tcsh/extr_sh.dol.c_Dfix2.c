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
struct blk_buf {int dummy; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  Dcp ; 
 int /*<<< orphan*/ * const* Dvp ; 
 scalar_t__ Dword (struct blk_buf*) ; 
 int /*<<< orphan*/  STRNULL ; 
 struct blk_buf* bb_alloc () ; 
 int /*<<< orphan*/ ** bb_finish (struct blk_buf*) ; 
 int /*<<< orphan*/  bb_free ; 
 int /*<<< orphan*/  cleanup_ignore (struct blk_buf*) ; 
 int /*<<< orphan*/  cleanup_push (struct blk_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (struct blk_buf*) ; 
 scalar_t__ dolcnt ; 
 scalar_t__ dolp ; 
 int /*<<< orphan*/  unDgetC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unDredc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (struct blk_buf*) ; 

__attribute__((used)) static Char **
Dfix2(Char *const *v)
{
    struct blk_buf *bb = bb_alloc();
    Char **vec;

    Dvp = v;
    Dcp = STRNULL;		/* Setup input vector for Dreadc */
    unDgetC(0);
    unDredc(0);			/* Clear out any old peeks (at error) */
    dolp = 0;
    dolcnt = 0;			/* Clear out residual $ expands (...) */
    cleanup_push(bb, bb_free);
    while (Dword(bb))
	continue;
    cleanup_ignore(bb);
    cleanup_until(bb);
    vec = bb_finish(bb);
    xfree(bb);
    return vec;
}
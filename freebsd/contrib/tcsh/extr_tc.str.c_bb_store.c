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
struct blk_buf {size_t len; size_t size; int /*<<< orphan*/ ** vec; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/ ** xrealloc (int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static void
bb_store(struct blk_buf *bb, Char *str)
{
    if (bb->len == bb->size) { /* Keep space for terminating NULL */
	if (bb->size == 0)
	    bb->size = 16; /* Arbitrary */
	else
	    bb->size *= 2;
	bb->vec = xrealloc(bb->vec, bb->size * sizeof (*bb->vec));
    }
    bb->vec[bb->len] = str;
}
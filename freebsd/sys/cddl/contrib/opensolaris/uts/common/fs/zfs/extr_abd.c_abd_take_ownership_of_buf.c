#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ boolean_t ;
struct TYPE_5__ {int abd_flags; int /*<<< orphan*/  abd_size; } ;
typedef  TYPE_1__ abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABDSTAT_BUMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ABDSTAT_INCR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ABD_FLAG_META ; 
 int ABD_FLAG_OWNER ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int abd_is_linear (TYPE_1__*) ; 
 int /*<<< orphan*/  abd_verify (TYPE_1__*) ; 
 int /*<<< orphan*/  abdstat_linear_cnt ; 
 int /*<<< orphan*/  abdstat_linear_data_size ; 

void
abd_take_ownership_of_buf(abd_t *abd, boolean_t is_metadata)
{
	ASSERT(abd_is_linear(abd));
	ASSERT(!(abd->abd_flags & ABD_FLAG_OWNER));
	abd_verify(abd);

	abd->abd_flags |= ABD_FLAG_OWNER;
	if (is_metadata) {
		abd->abd_flags |= ABD_FLAG_META;
	}

	ABDSTAT_BUMP(abdstat_linear_cnt);
	ABDSTAT_INCR(abdstat_linear_data_size, abd->abd_size);
}
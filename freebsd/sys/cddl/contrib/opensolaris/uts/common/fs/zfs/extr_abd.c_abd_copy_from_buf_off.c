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
struct buf_arg {void* member_0; } ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  abd_copy_from_buf_off_cb ; 
 int /*<<< orphan*/  abd_iterate_func (int /*<<< orphan*/ *,size_t,size_t,int /*<<< orphan*/ ,struct buf_arg*) ; 

void
abd_copy_from_buf_off(abd_t *abd, const void *buf, size_t off, size_t size)
{
	struct buf_arg ba_ptr = { (void *) buf };

	(void) abd_iterate_func(abd, off, size, abd_copy_from_buf_off_cb,
	    &ba_ptr);
}
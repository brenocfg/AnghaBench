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
struct talitos_ptr {int /*<<< orphan*/  eptr; int /*<<< orphan*/  len; int /*<<< orphan*/  len1; int /*<<< orphan*/  ptr; } ;

/* Variables and functions */

__attribute__((used)) static void copy_talitos_ptr(struct talitos_ptr *dst_ptr,
			     struct talitos_ptr *src_ptr, bool is_sec1)
{
	dst_ptr->ptr = src_ptr->ptr;
	if (is_sec1) {
		dst_ptr->len1 = src_ptr->len1;
	} else {
		dst_ptr->len = src_ptr->len;
		dst_ptr->eptr = src_ptr->eptr;
	}
}
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
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  abd_copy_to_buf_off (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

inline void
abd_copy_to_buf(void* buf, abd_t *abd, size_t size)
{
	abd_copy_to_buf_off(buf, abd, 0, size);
}
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
struct pt_buffer {int /*<<< orphan*/  cur_idx; int /*<<< orphan*/  cur; } ;

/* Variables and functions */
 size_t TOPA_ENTRY_SIZE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t pt_buffer_region_size(struct pt_buffer *buf)
{
	return TOPA_ENTRY_SIZE(buf->cur, buf->cur_idx);
}
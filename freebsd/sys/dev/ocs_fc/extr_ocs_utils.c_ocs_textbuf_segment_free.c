#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int buffer_length; struct TYPE_4__* buffer; int /*<<< orphan*/  user_allocated; } ;
typedef  TYPE_1__ ocs_textbuf_segment_t ;
typedef  int /*<<< orphan*/  ocs_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

__attribute__((used)) static void
ocs_textbuf_segment_free(ocs_t *ocs, ocs_textbuf_segment_t *segment)
{
	if (segment) {
		if (segment->buffer && !segment->user_allocated) {
			ocs_free(ocs, segment->buffer, segment->buffer_length);
		}
		ocs_free(ocs, segment, sizeof(*segment));
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ocs_textbuf_t ;
struct TYPE_3__ {int buffer_written; } ;
typedef  TYPE_1__ ocs_textbuf_segment_t ;
typedef  int int32_t ;

/* Variables and functions */
 TYPE_1__* ocs_textbuf_get_segment (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int32_t ocs_textbuf_ext_get_written(ocs_textbuf_t *textbuf, uint32_t idx)
{
	ocs_textbuf_segment_t *segment = ocs_textbuf_get_segment(textbuf, idx);
	if (segment == NULL) {
		return -1;
	}
	return segment->buffer_written;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int /*<<< orphan*/  segment_list; } ;
typedef  TYPE_1__ ocs_textbuf_t ;
struct TYPE_9__ {int /*<<< orphan*/  buffer_written; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_2__ ocs_textbuf_segment_t ;

/* Variables and functions */
 TYPE_2__* ocs_list_get_tail (int /*<<< orphan*/ *) ; 
 scalar_t__ ocs_segment_remaining (TYPE_2__*) ; 
 scalar_t__ ocs_textbuf_initialized (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_textbuf_segment_alloc (TYPE_1__*) ; 

void
ocs_textbuf_putc(ocs_textbuf_t *textbuf, uint8_t c)
{
	ocs_textbuf_segment_t *segment;

	if (ocs_textbuf_initialized(textbuf)) {
		segment = ocs_list_get_tail(&textbuf->segment_list);

		if (ocs_segment_remaining(segment)) {
			*(segment->buffer + segment->buffer_written++) = c;
		}
		if (ocs_segment_remaining(segment) == 0) {
			ocs_textbuf_segment_alloc(textbuf);
		}
	}
}
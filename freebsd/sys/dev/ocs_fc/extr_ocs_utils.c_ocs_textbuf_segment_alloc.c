#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int allocation_length; scalar_t__ total_allocation_length; scalar_t__ max_allocation_length; int /*<<< orphan*/  ocs; scalar_t__ extendable; int /*<<< orphan*/  segment_list; } ;
typedef  TYPE_1__ ocs_textbuf_t ;
struct TYPE_8__ {int buffer_length; scalar_t__ buffer_written; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_2__ ocs_textbuf_segment_t ;

/* Variables and functions */
 int OCS_M_NOWAIT ; 
 int OCS_M_ZERO ; 
 int /*<<< orphan*/  ocs_list_add_tail (int /*<<< orphan*/ *,TYPE_2__*) ; 
 void* ocs_malloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ocs_textbuf_segment_free (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static ocs_textbuf_segment_t *
ocs_textbuf_segment_alloc(ocs_textbuf_t *textbuf)
{
	ocs_textbuf_segment_t *segment = NULL;

	if (textbuf->extendable) {
		segment = ocs_malloc(textbuf->ocs, sizeof(*segment), OCS_M_ZERO | OCS_M_NOWAIT);
		if (segment != NULL) {
			segment->buffer = ocs_malloc(textbuf->ocs, textbuf->allocation_length, OCS_M_ZERO | OCS_M_NOWAIT);
			if (segment->buffer != NULL) {
				segment->buffer_length = textbuf->allocation_length;
				segment->buffer_written = 0;
				ocs_list_add_tail(&textbuf->segment_list, segment);
				textbuf->total_allocation_length += textbuf->allocation_length;

				/* If we've allocated our limit, then mark as not extendable */
				if (textbuf->total_allocation_length >= textbuf->max_allocation_length) {
					textbuf->extendable = 0;
				}

			} else {
				ocs_textbuf_segment_free(textbuf->ocs, segment);
				segment = NULL;
			}
		}
	}
	return segment;
}
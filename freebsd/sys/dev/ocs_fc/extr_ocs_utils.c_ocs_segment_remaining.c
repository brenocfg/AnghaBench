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
struct TYPE_3__ {scalar_t__ buffer_written; scalar_t__ buffer_length; } ;
typedef  TYPE_1__ ocs_textbuf_segment_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */

__attribute__((used)) static int32_t
ocs_segment_remaining(ocs_textbuf_segment_t *segment)
{
	return segment->buffer_length - segment->buffer_written;
}
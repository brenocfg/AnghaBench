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
struct TYPE_4__ {int /*<<< orphan*/  segment_list; } ;
typedef  TYPE_1__ ocs_textbuf_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_list_get_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_segment_remaining (int /*<<< orphan*/ ) ; 
 scalar_t__ ocs_textbuf_initialized (TYPE_1__*) ; 

int32_t
ocs_textbuf_remaining(ocs_textbuf_t *textbuf)
{
	if (ocs_textbuf_initialized(textbuf)) {
		return ocs_segment_remaining(ocs_list_get_head(&textbuf->segment_list));
	} else {
		return 0;
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  size; void* offset_last_wrap; void* offset_next_write; } ;

/* Variables and functions */
 TYPE_1__* header ; 
 void* logbuffer ; 
 int /*<<< orphan*/  logbuffer_size ; 
 void* loglastwrap ; 
 void* logwalk ; 

__attribute__((used)) static void store_log_markers(void) {
    header->offset_next_write = (logwalk - logbuffer);
    header->offset_last_wrap = (loglastwrap - logbuffer);
    header->size = logbuffer_size;
}
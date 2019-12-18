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
struct evbuffer_file_segment {scalar_t__ refcnt; void* cleanup_cb_arg; int /*<<< orphan*/  cleanup_cb; } ;
typedef  int /*<<< orphan*/  evbuffer_file_segment_cleanup_cb ;

/* Variables and functions */
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 

void evbuffer_file_segment_add_cleanup_cb(struct evbuffer_file_segment *seg,
	evbuffer_file_segment_cleanup_cb cb, void* arg)
{
	EVUTIL_ASSERT(seg->refcnt > 0);
	seg->cleanup_cb = cb;
	seg->cleanup_cb_arg = arg;
}
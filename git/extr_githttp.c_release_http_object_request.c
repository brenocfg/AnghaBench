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
struct http_object_request {int localfile; int /*<<< orphan*/  tmpfile; TYPE_1__* slot; int /*<<< orphan*/  url; } ;
struct TYPE_2__ {int /*<<< orphan*/ * callback_data; int /*<<< orphan*/ * callback_func; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  release_active_slot (TYPE_1__*) ; 
 int /*<<< orphan*/  strbuf_release (int /*<<< orphan*/ *) ; 

void release_http_object_request(struct http_object_request *freq)
{
	if (freq->localfile != -1) {
		close(freq->localfile);
		freq->localfile = -1;
	}
	FREE_AND_NULL(freq->url);
	if (freq->slot != NULL) {
		freq->slot->callback_func = NULL;
		freq->slot->callback_data = NULL;
		release_active_slot(freq->slot);
		freq->slot = NULL;
	}
	strbuf_release(&freq->tmpfile);
}
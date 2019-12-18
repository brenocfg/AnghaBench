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
struct auth_xfer {TYPE_1__* task_transfer; } ;
struct auth_chunk {struct auth_chunk* next; int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
struct TYPE_2__ {struct auth_chunk* chunks_last; struct auth_chunk* chunks_first; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (struct auth_chunk*) ; 
 int /*<<< orphan*/  memdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_limit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xfer_link_data(sldns_buffer* pkt, struct auth_xfer* xfr)
{
	/* alloc it */
	struct auth_chunk* e;
	e = (struct auth_chunk*)calloc(1, sizeof(*e));
	if(!e) return 0;
	e->next = NULL;
	e->len = sldns_buffer_limit(pkt);
	e->data = memdup(sldns_buffer_begin(pkt), e->len);
	if(!e->data) {
		free(e);
		return 0;
	}

	/* alloc succeeded, link into list */
	if(!xfr->task_transfer->chunks_first)
		xfr->task_transfer->chunks_first = e;
	if(xfr->task_transfer->chunks_last)
		xfr->task_transfer->chunks_last->next = e;
	xfr->task_transfer->chunks_last = e;
	return 1;
}
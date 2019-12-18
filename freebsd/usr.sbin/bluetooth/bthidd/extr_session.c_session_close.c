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
typedef  TYPE_2__* bthid_session_p ;
struct TYPE_8__ {int intr; int ctrl; int vkbd; int umouse; int ukbd; struct TYPE_8__* keys2; struct TYPE_8__* keys1; struct TYPE_8__* ctx; TYPE_1__* srv; } ;
struct TYPE_7__ {int maxfd; int /*<<< orphan*/  rfdset; int /*<<< orphan*/  wfdset; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD_CLR (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  next ; 

void
session_close(bthid_session_p s)
{
	assert(s != NULL);
	assert(s->srv != NULL);

	LIST_REMOVE(s, next);

	if (s->intr != -1) {
		FD_CLR(s->intr, &s->srv->rfdset);
		FD_CLR(s->intr, &s->srv->wfdset);
		close(s->intr);

		if (s->srv->maxfd == s->intr)
			s->srv->maxfd --;
	}

	if (s->ctrl != -1) {
		FD_CLR(s->ctrl, &s->srv->rfdset);
		FD_CLR(s->ctrl, &s->srv->wfdset);
		close(s->ctrl);

		if (s->srv->maxfd == s->ctrl)
			s->srv->maxfd --;
	}

	if (s->vkbd != -1) {
		FD_CLR(s->vkbd, &s->srv->rfdset);
		close(s->vkbd);

		if (s->srv->maxfd == s->vkbd)
			s->srv->maxfd --;
	}

	if (s->umouse != -1)
		close(s->umouse);

	if (s->ukbd != -1) {
		FD_CLR(s->ukbd, &s->srv->rfdset);
		close(s->ukbd);

		if (s->srv->maxfd == s->ukbd)
			s->srv->maxfd --;
	}

	free(s->ctx);
	free(s->keys1);
	free(s->keys2);

	memset(s, 0, sizeof(*s));
	free(s);
}
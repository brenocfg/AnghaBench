#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hid_device_p ;
typedef  TYPE_2__* bthid_session_p ;
typedef  TYPE_3__* bthid_server_p ;
struct TYPE_11__ {int /*<<< orphan*/  sessions; } ;
struct TYPE_10__ {int ctrl; int intr; int vkbd; int ukbd; int umouse; struct TYPE_10__* keys1; int /*<<< orphan*/ * keys2; scalar_t__ obutt; int /*<<< orphan*/  state; int /*<<< orphan*/ * ctx; int /*<<< orphan*/  bdaddr; TYPE_3__* srv; } ;
struct TYPE_9__ {int /*<<< orphan*/  bdaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSED ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 void* bit_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  kbd_maxkey () ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  next ; 

bthid_session_p
session_open(bthid_server_p srv, hid_device_p const d)
{
	bthid_session_p	s;

	assert(srv != NULL);
	assert(d != NULL);

	if ((s = (bthid_session_p) malloc(sizeof(*s))) == NULL)
		return (NULL);

	s->srv = srv;  
	memcpy(&s->bdaddr, &d->bdaddr, sizeof(s->bdaddr));
	s->ctrl = -1;
	s->intr = -1;
	s->vkbd = -1;
	s->ctx = NULL;
	s->state = CLOSED;
	s->ukbd = -1;
	s->umouse = -1;
	s->obutt = 0;

	s->keys1 = bit_alloc(kbd_maxkey());
	if (s->keys1 == NULL) {
		free(s);
		return (NULL);
	}

	s->keys2 = bit_alloc(kbd_maxkey());
	if (s->keys2 == NULL) {
		free(s->keys1);
		free(s);
		return (NULL);
	}

	LIST_INSERT_HEAD(&srv->sessions, s, next);

	return (s);
}
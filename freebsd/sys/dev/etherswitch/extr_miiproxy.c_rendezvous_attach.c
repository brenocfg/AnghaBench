#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int (* callback ) (int /*<<< orphan*/ ,struct rendezvous_entry*) ;} ;
struct TYPE_3__ {int (* callback ) (int /*<<< orphan*/ ,struct rendezvous_entry*) ;} ;
struct rendezvous_entry {TYPE_2__ proxy; TYPE_1__ target; } ;
struct rendezvous_endpoint {int /*<<< orphan*/ * callback; int /*<<< orphan*/ * device; } ;

/* Variables and functions */
 int /*<<< orphan*/  RENDEZVOUS_ATTACH ; 
 int /*<<< orphan*/  RENDEZVOUS_DETACH ; 
 int stub1 (int /*<<< orphan*/ ,struct rendezvous_entry*) ; 
 int stub2 (int /*<<< orphan*/ ,struct rendezvous_entry*) ; 
 int stub3 (int /*<<< orphan*/ ,struct rendezvous_entry*) ; 

__attribute__((used)) static int
rendezvous_attach(struct rendezvous_entry *e, struct rendezvous_endpoint *ep)
{
	int error;

	error = e->proxy.callback(RENDEZVOUS_ATTACH, e);
	if (error == 0) {
		error = e->target.callback(RENDEZVOUS_ATTACH, e);
		if (error != 0) {
			e->proxy.callback(RENDEZVOUS_DETACH, e);
			ep->device = NULL;
			ep->callback = NULL;
		}
	}
	return (error);
}
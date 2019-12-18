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
struct intr_handler {int /*<<< orphan*/  ih_name; struct intr_event* ih_event; } ;
struct intr_event {void* ie_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 

void *
intr_handler_source(void *cookie)
{
	struct intr_handler *ih;
	struct intr_event *ie;

	ih = (struct intr_handler *)cookie;
	if (ih == NULL)
		return (NULL);
	ie = ih->ih_event;
	KASSERT(ie != NULL,
	    ("interrupt handler \"%s\" has a NULL interrupt event",
	    ih->ih_name));
	return (ie->ie_source);
}
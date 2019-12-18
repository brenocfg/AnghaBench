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
struct bhndb_resources {int /*<<< orphan*/  bus_intrs; } ;
struct bhndb_intr_handler {int ih_active; int /*<<< orphan*/  ih_cookiep; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  STAILQ_REMOVE (int /*<<< orphan*/ *,struct bhndb_intr_handler*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bhndb_intr_handler* bhndb_find_intr_handler (struct bhndb_resources*,struct bhndb_intr_handler*) ; 
 int /*<<< orphan*/  bhndb_intr_handler ; 
 int /*<<< orphan*/  ih_link ; 

void
bhndb_deregister_intr_handler(struct bhndb_resources *br,
    struct bhndb_intr_handler *ih)
{
	KASSERT(ih->ih_active, ("duplicate deregistration of interrupt "
	    "handler %p", ih->ih_cookiep));

	KASSERT(bhndb_find_intr_handler(br, ih) == ih,
	    ("unknown interrupt handler %p", ih));

	STAILQ_REMOVE(&br->bus_intrs, ih, bhndb_intr_handler, ih_link);
	ih->ih_active = false;
}
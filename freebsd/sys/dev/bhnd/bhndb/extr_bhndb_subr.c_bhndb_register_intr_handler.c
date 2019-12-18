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
struct bhndb_intr_handler {int ih_active; int /*<<< orphan*/ * ih_cookiep; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  STAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct bhndb_intr_handler*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ih_link ; 

void
bhndb_register_intr_handler(struct bhndb_resources *br,
    struct bhndb_intr_handler *ih)
{
	KASSERT(!ih->ih_active, ("duplicate registration of interrupt "
	    "handler %p", ih->ih_cookiep));
	KASSERT(ih->ih_cookiep != NULL, ("missing cookiep"));

	ih->ih_active = true;
	STAILQ_INSERT_HEAD(&br->bus_intrs, ih, ih_link);
}
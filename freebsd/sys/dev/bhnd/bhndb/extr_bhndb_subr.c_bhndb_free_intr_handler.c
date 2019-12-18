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
struct bhndb_intr_handler {int /*<<< orphan*/  ih_cookiep; int /*<<< orphan*/  ih_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_BHND ; 
 int /*<<< orphan*/  free (struct bhndb_intr_handler*,int /*<<< orphan*/ ) ; 

void
bhndb_free_intr_handler(struct bhndb_intr_handler *ih)
{
	KASSERT(!ih->ih_active, ("free of active interrupt handler %p",
	    ih->ih_cookiep));

	free(ih, M_BHND);
}
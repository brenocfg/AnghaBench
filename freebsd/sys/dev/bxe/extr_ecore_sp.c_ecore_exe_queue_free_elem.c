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
struct ecore_exeq_elem {int dummy; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_FREE (struct bxe_softc*,struct ecore_exeq_elem*,int) ; 
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*) ; 

__attribute__((used)) static inline void ecore_exe_queue_free_elem(struct bxe_softc *sc,
					     struct ecore_exeq_elem *elem)
{
	ECORE_MSG(sc, "Deleting an exe_queue element\n");
	ECORE_FREE(sc, elem, sizeof(*elem));
}
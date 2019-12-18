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
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*) ; 
 struct ecore_exeq_elem* ECORE_ZALLOC (int,int /*<<< orphan*/ ,struct bxe_softc*) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 

__attribute__((used)) static inline struct ecore_exeq_elem *ecore_exe_queue_alloc_elem(
	struct bxe_softc *sc)
{
	ECORE_MSG(sc, "Allocating a new exe_queue element\n");
	return ECORE_ZALLOC(sizeof(struct ecore_exeq_elem), GFP_ATOMIC,
			    sc);
}
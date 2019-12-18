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
struct ecore_func_sp_obj {int /*<<< orphan*/  pending; } ;
struct bxe_softc {int dummy; } ;
typedef  enum ecore_func_cmd { ____Placeholder_ecore_func_cmd } ecore_func_cmd ;

/* Variables and functions */
 int ecore_state_wait (struct bxe_softc*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ecore_func_wait_comp(struct bxe_softc *sc,
				struct ecore_func_sp_obj *o,
				enum ecore_func_cmd cmd)
{
	return ecore_state_wait(sc, cmd, &o->pending);
}
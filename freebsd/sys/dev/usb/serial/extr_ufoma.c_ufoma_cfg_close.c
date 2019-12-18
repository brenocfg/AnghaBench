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
struct ufoma_softc {int dummy; } ;
struct ucom_softc {struct ufoma_softc* sc_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  UMCPC_ACM_MODE_DEACTIVATED ; 
 int /*<<< orphan*/  ufoma_cfg_activate_state (struct ufoma_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ufoma_cfg_close(struct ucom_softc *ucom)
{
	struct ufoma_softc *sc = ucom->sc_parent;

	ufoma_cfg_activate_state(sc, UMCPC_ACM_MODE_DEACTIVATED);
}
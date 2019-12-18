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
struct ucom_softc {struct uchcom_softc* sc_parent; } ;
struct uchcom_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  uchcom_update_status (struct uchcom_softc*) ; 
 int /*<<< orphan*/  uchcom_update_version (struct uchcom_softc*) ; 

__attribute__((used)) static void
uchcom_cfg_open(struct ucom_softc *ucom)
{
	struct uchcom_softc *sc = ucom->sc_parent;

	DPRINTF("\n");

	uchcom_update_version(sc);
	uchcom_update_status(sc);
}
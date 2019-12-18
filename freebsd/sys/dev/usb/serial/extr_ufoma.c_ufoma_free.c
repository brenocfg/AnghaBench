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
struct ucom_softc {int /*<<< orphan*/  sc_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ufoma_free_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ufoma_free(struct ucom_softc *ucom)
{
	ufoma_free_softc(ucom->sc_parent);
}
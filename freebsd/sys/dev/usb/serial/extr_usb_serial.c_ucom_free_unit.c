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
struct ucom_super_softc {int sc_flag; int /*<<< orphan*/  sc_unit; } ;

/* Variables and functions */
 int UCOM_FLAG_FREE_UNIT ; 
 int /*<<< orphan*/  ucom_unit_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ucom_free_unit(struct ucom_super_softc *ssc)
{
	if (!(ssc->sc_flag & UCOM_FLAG_FREE_UNIT))
		return;

	ucom_unit_free(ssc->sc_unit);

	ssc->sc_flag &= ~UCOM_FLAG_FREE_UNIT;
}
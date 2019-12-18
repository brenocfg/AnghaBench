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
struct exca_softc {int /*<<< orphan*/  pccarddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_DETACH_CARD (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 

void
exca_removal(struct exca_softc *exca)
{
	if (device_is_attached(exca->pccarddev))
		CARD_DETACH_CARD(exca->pccarddev);
}
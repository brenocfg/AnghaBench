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
struct bnxt_softc {int /*<<< orphan*/  doorbell_bar; int /*<<< orphan*/  hwrm_bar; } ;

/* Variables and functions */
 int bnxt_map_bar (struct bnxt_softc*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int
bnxt_pci_mapping(struct bnxt_softc *softc)
{
	int rc;

	rc = bnxt_map_bar(softc, &softc->hwrm_bar, 0, true);
	if (rc)
		return rc;

	rc = bnxt_map_bar(softc, &softc->doorbell_bar, 2, false);

	return rc;
}
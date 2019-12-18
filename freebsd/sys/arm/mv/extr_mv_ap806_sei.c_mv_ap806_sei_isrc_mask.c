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
typedef  scalar_t__ uint32_t ;
struct mv_ap806_sei_softc {int dummy; } ;
struct mv_ap806_sei_irqsrc {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  GICP_SEMR (int /*<<< orphan*/ ) ; 
 int GICP_SEMR_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MV_AP806_SEI_LOCK (struct mv_ap806_sei_softc*) ; 
 int /*<<< orphan*/  MV_AP806_SEI_UNLOCK (struct mv_ap806_sei_softc*) ; 
 scalar_t__ RD4 (struct mv_ap806_sei_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR4 (struct mv_ap806_sei_softc*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void
mv_ap806_sei_isrc_mask(struct mv_ap806_sei_softc *sc,
     struct mv_ap806_sei_irqsrc *sisrc, uint32_t val)
{
	uint32_t tmp;
	int bit;

	bit = GICP_SEMR_BIT(sisrc->irq);
	MV_AP806_SEI_LOCK(sc);
	tmp = RD4(sc, GICP_SEMR(sisrc->irq));
	if (val != 0)
		tmp |= 1 << bit;
	else
		tmp &= ~(1 << bit);
	WR4(sc, GICP_SEMR(sisrc->irq), tmp);
	MV_AP806_SEI_UNLOCK(sc);
}
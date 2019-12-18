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
struct mv_ap806_sei_softc {int dummy; } ;
struct mv_ap806_sei_irqsrc {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  GICP_SECR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GICP_SECR_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR4 (struct mv_ap806_sei_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
mv_ap806_sei_isrc_eoi(struct mv_ap806_sei_softc *sc,
     struct mv_ap806_sei_irqsrc *sisrc)
{

	WR4(sc, GICP_SECR(sisrc->irq), GICP_SECR_BIT(sisrc->irq));
}
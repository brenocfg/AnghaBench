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
typedef  unsigned int u_int ;
struct mtk_pic_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_INTDIS ; 
 int /*<<< orphan*/  WRITE4 (struct mtk_pic_softc*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void
pic_irq_mask(struct mtk_pic_softc *sc, u_int irq)
{

	WRITE4(sc, MTK_INTDIS, (1u << (irq)));
}
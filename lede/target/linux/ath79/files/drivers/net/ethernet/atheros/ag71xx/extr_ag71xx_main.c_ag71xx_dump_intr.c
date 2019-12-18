#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ag71xx {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int AG71XX_INT_RX_BE ; 
 int AG71XX_INT_RX_OF ; 
 int AG71XX_INT_RX_PR ; 
 int AG71XX_INT_TX_BE ; 
 int AG71XX_INT_TX_PS ; 
 int AG71XX_INT_TX_UR ; 
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,char*,int,char*,char*,char*,char*,char*,char*) ; 

__attribute__((used)) static inline void ag71xx_dump_intr(struct ag71xx *ag, char *label, u32 intr)
{
	DBG("%s: %s intr=%08x %s%s%s%s%s%s\n",
		ag->dev->name, label, intr,
		(intr & AG71XX_INT_TX_PS) ? "TXPS " : "",
		(intr & AG71XX_INT_TX_UR) ? "TXUR " : "",
		(intr & AG71XX_INT_TX_BE) ? "TXBE " : "",
		(intr & AG71XX_INT_RX_PR) ? "RXPR " : "",
		(intr & AG71XX_INT_RX_OF) ? "RXOF " : "",
		(intr & AG71XX_INT_RX_BE) ? "RXBE " : "");
}
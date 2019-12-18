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
struct sis_rxdesc {TYPE_1__* rx_desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  sis_cmdsts; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIS_RXLEN ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
sis_discard_rxbuf(struct sis_rxdesc *rxd)
{

	rxd->rx_desc->sis_cmdsts = htole32(SIS_RXLEN);
}
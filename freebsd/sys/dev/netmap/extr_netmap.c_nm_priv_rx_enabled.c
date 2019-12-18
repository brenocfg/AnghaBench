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
struct netmap_priv_d {scalar_t__* np_qfirst; scalar_t__* np_qlast; } ;

/* Variables and functions */
 size_t NR_RX ; 

__attribute__((used)) static int
nm_priv_rx_enabled(struct netmap_priv_d *priv)
{
	return (priv->np_qfirst[NR_RX] != priv->np_qlast[NR_RX]);
}
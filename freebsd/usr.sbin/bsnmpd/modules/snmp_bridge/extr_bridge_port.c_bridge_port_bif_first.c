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
struct bridge_port {int dummy; } ;
struct bridge_if {struct bridge_port* f_bp; } ;

/* Variables and functions */

struct bridge_port *
bridge_port_bif_first(struct bridge_if *bif)
{
	return (bif->f_bp);
}
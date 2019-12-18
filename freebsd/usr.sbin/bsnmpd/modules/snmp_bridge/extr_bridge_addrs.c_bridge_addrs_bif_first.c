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
struct tp_entry {int dummy; } ;
struct bridge_if {struct tp_entry* f_tpa; } ;

/* Variables and functions */

struct tp_entry *
bridge_addrs_bif_first(struct bridge_if *bif)
{
	return (bif->f_tpa);
}
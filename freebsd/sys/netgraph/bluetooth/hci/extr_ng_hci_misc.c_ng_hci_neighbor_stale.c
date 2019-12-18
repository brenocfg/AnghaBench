#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timeval {scalar_t__ tv_sec; } ;
typedef  TYPE_2__* ng_hci_neighbor_p ;
struct TYPE_4__ {scalar_t__ tv_sec; } ;
struct TYPE_5__ {TYPE_1__ updated; } ;

/* Variables and functions */
 scalar_t__ bluetooth_hci_max_neighbor_age () ; 
 int /*<<< orphan*/  getmicrotime (struct timeval*) ; 

int
ng_hci_neighbor_stale(ng_hci_neighbor_p n)
{
	struct timeval	now;

	getmicrotime(&now);

	return (now.tv_sec - n->updated.tv_sec > bluetooth_hci_max_neighbor_age());
}
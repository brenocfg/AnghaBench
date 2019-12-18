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
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  ng_hci_unit_p ;

/* Variables and functions */
 int /*<<< orphan*/  NG_FREE_M (struct mbuf*) ; 

__attribute__((used)) static int le_connection_update(ng_hci_unit_p unit, struct mbuf *event)
{
	int error = 0;
	/*TBD*/
	
	NG_FREE_M(event);
	return error;

}
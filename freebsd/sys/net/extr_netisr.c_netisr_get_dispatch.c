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
typedef  scalar_t__ u_int ;
struct netisr_proto {scalar_t__ np_dispatch; } ;

/* Variables and functions */
 scalar_t__ NETISR_DISPATCH_DEFAULT ; 
 scalar_t__ netisr_dispatch_policy ; 

__attribute__((used)) static u_int
netisr_get_dispatch(struct netisr_proto *npp)
{

	/*
	 * Protocol-specific configuration overrides the global default.
	 */
	if (npp->np_dispatch != NETISR_DISPATCH_DEFAULT)
		return (npp->np_dispatch);
	return (netisr_dispatch_policy);
}
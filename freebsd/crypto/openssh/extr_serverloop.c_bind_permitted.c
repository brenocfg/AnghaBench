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
typedef  scalar_t__ uid_t ;

/* Variables and functions */
 int IPPORT_RESERVED ; 
 scalar_t__ use_privsep ; 

__attribute__((used)) static int
bind_permitted(int port, uid_t uid)
{
	if (use_privsep)
		return 1; /* allow system to decide */
	if (port < IPPORT_RESERVED && uid != 0)
		return 0;
	return 1;
}
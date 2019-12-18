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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ u_char ;

/* Variables and functions */
 scalar_t__ EUI48_LOCALLY_ADMINISTERED ; 
 int /*<<< orphan*/  arc4rand (scalar_t__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
create_random_local_eui48(u_char *eaddr)
{
	static uint8_t counter = 0;

	eaddr[0] = EUI48_LOCALLY_ADMINISTERED;
	arc4rand(&eaddr[1], 4, 0);
	eaddr[5] = counter++;
}
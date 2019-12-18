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

/* Variables and functions */
 int /*<<< orphan*/  _dorand48 (scalar_t__*) ; 
 scalar_t__* _rand48_seed ; 

long
lrand48(void)
{
	_dorand48(_rand48_seed);
	return ((long) _rand48_seed[2] << 15) + ((long) _rand48_seed[1] >> 1);
}
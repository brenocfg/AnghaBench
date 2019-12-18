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
 int /*<<< orphan*/  _dorand48 (unsigned short*) ; 
 double ldexp (double,int) ; 

double
erand48(unsigned short xseed[3])
{
	_dorand48(xseed);
	return ldexp((double) xseed[0], -48) +
	       ldexp((double) xseed[1], -32) +
	       ldexp((double) xseed[2], -16);
}
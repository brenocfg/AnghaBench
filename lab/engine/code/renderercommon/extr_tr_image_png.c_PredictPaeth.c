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

/* Variables and functions */
 int abs (int) ; 

__attribute__((used)) static uint8_t PredictPaeth(uint8_t a, uint8_t b, uint8_t c)
{
	/*
	 *  a == Left
	 *  b == Up
	 *  c == UpLeft
	 */

	uint8_t Pr;
	int p;
	int pa, pb, pc;

	p  = ((int) a) + ((int) b) - ((int) c);
	pa = abs(p - ((int) a));
	pb = abs(p - ((int) b));
	pc = abs(p - ((int) c));

	if((pa <= pb) && (pa <= pc))
	{
		Pr = a;
	}
	else if(pb <= pc)
	{
		Pr = b;
	}
	else
	{
		Pr = c;
	}

	return(Pr);

}
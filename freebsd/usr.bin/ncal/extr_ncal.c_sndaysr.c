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
struct date {int dummy; } ;

/* Variables and functions */
 int ndaysg (struct date*) ; 
 int ndaysj (struct date*) ; 
 scalar_t__ nswitch ; 

__attribute__((used)) static int
sndaysr(struct date *d)
{

	if (nswitch != 0)
		if (nswitch < ndaysj(d))
			return (ndaysg(d));
		else
			return (ndaysj(d));
	else
		return ndaysg(d);
}
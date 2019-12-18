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
 double atof (char const*) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 

__attribute__((used)) static int
getrate(const char *val, const char *tag)
{
	double v = atof(val);
	int rate;

	rate = (int) (2*v);
	if (rate != 2*v)
		errx(-1, "invalid %s rate (must be .5 Mb/s units)", tag);
	return rate;		/* NB: returns 2x the specified value */
}
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
 int /*<<< orphan*/  errx (int,char*,char const*,long,...) ; 
 int /*<<< orphan*/  optarg ; 
 long strtol (int /*<<< orphan*/ ,char**,int) ; 

__attribute__((used)) static long
numarg(const char *meaning, long vmin, long vmax)
{
	char *p;
	long val;

	val = strtol(optarg, &p, 10);
	if (*p)
		errx(1, "illegal %s -- %s", meaning, optarg);
	if (val < vmin || (vmax && val > vmax))
		errx(1, "%s must be between %ld and %ld", meaning, vmin, vmax);
	return (val);
}
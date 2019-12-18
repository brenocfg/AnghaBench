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
struct ratemedia {scalar_t__ match; int media; } ;

/* Variables and functions */
 int IFM_AUTO ; 

__attribute__((used)) static int
findmedia(const struct ratemedia rates[], int n, u_int match)
{
	int i;

	for (i = 0; i < n; i++)
		if (rates[i].match == match)
			return rates[i].media;
	return IFM_AUTO;
}
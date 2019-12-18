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
struct rtentry {int rt_flags; } ;

/* Variables and functions */
 int RTF_DYNAMIC ; 
 int RTF_HOST ; 
 int RTF_UP ; 

__attribute__((used)) static int
nd6_isdynrte(const struct rtentry *rt, void *xap)
{

	if (rt->rt_flags == (RTF_UP | RTF_HOST | RTF_DYNAMIC))
		return (1);

	return (0);
}
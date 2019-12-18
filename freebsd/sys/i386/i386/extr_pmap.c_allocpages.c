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
typedef  int u_long ;
typedef  int u_int ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  bzero (void*,int) ; 

__attribute__((used)) static u_long
allocpages(u_int cnt, u_long *physfree)
{
	u_long res;

	res = *physfree;
	*physfree += PAGE_SIZE * cnt;
	bzero((void *)res, PAGE_SIZE * cnt);
	return (res);
}
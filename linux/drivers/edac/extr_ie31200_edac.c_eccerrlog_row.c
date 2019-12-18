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
typedef  int u64 ;

/* Variables and functions */
 int IE31200_ECCERRLOG_RANK_BITS ; 
 int IE31200_ECCERRLOG_RANK_SHIFT ; 

__attribute__((used)) static int eccerrlog_row(u64 log)
{
	return ((log & IE31200_ECCERRLOG_RANK_BITS) >>
				IE31200_ECCERRLOG_RANK_SHIFT);
}
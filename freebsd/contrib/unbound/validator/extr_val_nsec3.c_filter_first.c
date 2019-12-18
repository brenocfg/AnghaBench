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
struct ub_packed_rrset_key {int dummy; } ;
struct nsec3_filter {int dummy; } ;

/* Variables and functions */
 struct ub_packed_rrset_key* filter_next (struct nsec3_filter*,size_t*,int*) ; 

__attribute__((used)) static struct ub_packed_rrset_key*
filter_first(struct nsec3_filter* filter, size_t* rrsetnum, int* rrnum)
{
	*rrsetnum = 0;
	*rrnum = -1;
	return filter_next(filter, rrsetnum, rrnum);
}
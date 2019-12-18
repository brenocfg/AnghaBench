#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {scalar_t__ data; } ;
struct ub_packed_rrset_key {TYPE_1__ entry; } ;
struct packed_rrset_data {scalar_t__ count; } ;

/* Variables and functions */
 scalar_t__ nsec3_has_type (struct ub_packed_rrset_key*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nsec3_no_type(struct ub_packed_rrset_key* k, uint16_t t)
{
	int count = (int)((struct packed_rrset_data*)k->entry.data)->count;
	int i;
	for(i=0; i<count; i++)
		if(nsec3_has_type(k, i, t))
			return 0;
	return 1;
}
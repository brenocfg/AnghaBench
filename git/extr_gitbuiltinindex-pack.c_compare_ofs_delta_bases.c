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
typedef  scalar_t__ off_t ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */

__attribute__((used)) static int compare_ofs_delta_bases(off_t offset1, off_t offset2,
				   enum object_type type1,
				   enum object_type type2)
{
	int cmp = type1 - type2;
	if (cmp)
		return cmp;
	return offset1 < offset2 ? -1 :
	       offset1 > offset2 ?  1 :
	       0;
}
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
typedef  size_t u_int ;
typedef  int /*<<< orphan*/  cap_rights_t ;
struct TYPE_2__ {int /*<<< orphan*/  cd_desc; int /*<<< orphan*/  cd_right; } ;

/* Variables and functions */
 TYPE_1__* cap_desc ; 
 size_t cap_desc_count ; 
 scalar_t__ cap_rights_is_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
width_capability(cap_rights_t *rightsp)
{
	u_int count, i, width;

	count = 0;
	width = 0;
	for (i = 0; i < cap_desc_count; i++) {
		if (cap_rights_is_set(rightsp, cap_desc[i].cd_right)) {
			width += strlen(cap_desc[i].cd_desc);
			if (count)
				width++;
			count++;
		}
	}
	return (width);
}
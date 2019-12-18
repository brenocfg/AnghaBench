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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  busdma_tag_t ;
typedef  int busdma_md_t ;

/* Variables and functions */
 int bd_md_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int errno ; 

int
busdma_md_create(busdma_tag_t tag, u_int flags, busdma_md_t *out_p)
{
	int res;

	res = bd_md_create(tag, flags);
	if (res == -1)
		return (errno);
	*out_p = res;
	return (0);
}
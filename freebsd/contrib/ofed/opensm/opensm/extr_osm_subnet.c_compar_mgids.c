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
typedef  int /*<<< orphan*/  ib_gid_t ;

/* Variables and functions */
 int memcmp (void const*,void const*,int) ; 

__attribute__((used)) static int compar_mgids(const void *m1, const void *m2)
{
	return memcmp(m1, m2, sizeof(ib_gid_t));
}
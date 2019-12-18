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
struct blame_entry {scalar_t__ lno; } ;

/* Variables and functions */

__attribute__((used)) static int compare_blame_final(const void *p1, const void *p2)
{
	return ((struct blame_entry *)p1)->lno > ((struct blame_entry *)p2)->lno
		? 1 : -1;
}
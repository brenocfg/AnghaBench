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
struct unrhdr {int dummy; } ;
struct unr {struct unrhdr* ptr; } ;

/* Variables and functions */

__attribute__((used)) static __inline int
is_bitmap(struct unrhdr *uh, struct unr *up)
{
	return (up->ptr != uh && up->ptr != NULL);
}
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
struct mm_struct {int dummy; } ;
struct ldt_struct {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
map_ldt_struct(struct mm_struct *mm, struct ldt_struct *ldt, int slot)
{
	return 0;
}
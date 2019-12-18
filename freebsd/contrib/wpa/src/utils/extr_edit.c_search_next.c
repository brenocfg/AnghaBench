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

/* Variables and functions */
 int /*<<< orphan*/  search_find () ; 
 int /*<<< orphan*/  search_redraw () ; 
 int /*<<< orphan*/  search_skip ; 

__attribute__((used)) static void search_next(void)
{
	search_skip++;
	search_find();
	search_redraw();
}
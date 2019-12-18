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
struct level_stack {struct level_stack* next; } ;

/* Variables and functions */
 struct level_stack* g_ls ; 

__attribute__((used)) static void
_push_ls(struct level_stack *ls)
{

	ls->next = g_ls;
	g_ls = ls;
}
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
struct blame_entry {void* next; } ;

/* Variables and functions */

__attribute__((used)) static void set_next_blame(void *p1, void *p2)
{
	((struct blame_entry *)p1)->next = p2;
}
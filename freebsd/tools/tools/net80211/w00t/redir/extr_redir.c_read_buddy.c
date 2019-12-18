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
struct params {int buddy_got; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_buddy_data (struct params*) ; 
 int /*<<< orphan*/  read_buddy_head (struct params*) ; 

void read_buddy(struct params *p)
{
	if (p->buddy_got < 4)
		read_buddy_head(p);
	else
		read_buddy_data(p);
}
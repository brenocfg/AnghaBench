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
struct iter_hints {int dummy; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 

struct iter_hints* 
hints_create(void)
{
	struct iter_hints* hints = (struct iter_hints*)calloc(1,
		sizeof(struct iter_hints));
	if(!hints)
		return NULL;
	return hints;
}
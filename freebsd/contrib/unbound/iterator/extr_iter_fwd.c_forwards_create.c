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
struct iter_forwards {int dummy; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 

struct iter_forwards* 
forwards_create(void)
{
	struct iter_forwards* fwd = (struct iter_forwards*)calloc(1,
		sizeof(struct iter_forwards));
	if(!fwd)
		return NULL;
	return fwd;
}
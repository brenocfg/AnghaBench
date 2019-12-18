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
struct val_neg_data {struct val_neg_data* prev; struct val_neg_data* next; } ;
struct val_neg_cache {struct val_neg_data* first; struct val_neg_data* last; } ;

/* Variables and functions */

__attribute__((used)) static void neg_lru_front(struct val_neg_cache* neg, 
	struct val_neg_data* data)
{
	data->prev = NULL;
	data->next = neg->first;
	if(!neg->first)
		neg->last = data;
	else	neg->first->prev = data;
	neg->first = data;
}
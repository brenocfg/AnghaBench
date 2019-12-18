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
typedef  int /*<<< orphan*/  uint8_t ;
struct config_strbytelist {char* str; size_t str2len; struct config_strbytelist* next; int /*<<< orphan*/ * str2; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 

int
cfg_strbytelist_insert(struct config_strbytelist** head, char* item,
	uint8_t* i2, size_t i2len)
{
	struct config_strbytelist* s;
	if(!item || !i2 || !head)
		return 0;
	s = (struct config_strbytelist*)calloc(1, sizeof(*s));
	if(!s)
		return 0;
	s->str = item;
	s->str2 = i2;
	s->str2len = i2len;
	s->next = *head;
	*head = s;
	return 1;
}
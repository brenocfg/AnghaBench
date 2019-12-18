#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned char* data; struct TYPE_2__* next; } ;

/* Variables and functions */
 size_t PAGE_KEY_DATA_SIZE ; 
 TYPE_1__* page_key_wp ; 
 size_t page_key_wx ; 

void page_key_memorize(unsigned long *pfn)
{
	page_key_wp->data[page_key_wx] = *(unsigned char *) pfn;
	*(unsigned char *) pfn = 0;
	if (++page_key_wx < PAGE_KEY_DATA_SIZE)
		return;
	page_key_wp = page_key_wp->next;
	page_key_wx = 0;
}
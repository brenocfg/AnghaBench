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
 char* __entry_text_end ; 
 char* __entry_text_start ; 
 char* __irqentry_text_end ; 
 char* __irqentry_text_start ; 

__attribute__((used)) static bool in_entry_code(unsigned long ip)
{
	char *addr = (char *)ip;

	if (addr >= __entry_text_start && addr < __entry_text_end)
		return true;

	if (addr >= __irqentry_text_start && addr < __irqentry_text_end)
		return true;

	return false;
}
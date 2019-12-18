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
struct excludes {char* pattern; struct excludes* next; } ;

/* Variables and functions */
 struct excludes* excludes_list ; 
 struct excludes* xmalloc (int) ; 

void
push_excludes(char *pattern)
{
	struct excludes *entry;

	entry = xmalloc(sizeof(*entry));
	entry->pattern = pattern;
	entry->next = excludes_list;
	excludes_list = entry;
}
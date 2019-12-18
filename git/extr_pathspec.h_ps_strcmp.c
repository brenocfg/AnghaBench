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
struct pathspec_item {int magic; } ;

/* Variables and functions */
 int PATHSPEC_ICASE ; 
 int strcasecmp (char const*,char const*) ; 
 int strcmp (char const*,char const*) ; 

__attribute__((used)) static inline int ps_strcmp(const struct pathspec_item *item,
			    const char *s1, const char *s2)
{
	if (item->magic & PATHSPEC_ICASE)
		return strcasecmp(s1, s2);
	else
		return strcmp(s1, s2);
}
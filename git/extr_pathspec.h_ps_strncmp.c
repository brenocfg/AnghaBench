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
 int strncasecmp (char const*,char const*,size_t) ; 
 int strncmp (char const*,char const*,size_t) ; 

__attribute__((used)) static inline int ps_strncmp(const struct pathspec_item *item,
			     const char *s1, const char *s2, size_t n)
{
	if (item->magic & PATHSPEC_ICASE)
		return strncasecmp(s1, s2, n);
	else
		return strncmp(s1, s2, n);
}
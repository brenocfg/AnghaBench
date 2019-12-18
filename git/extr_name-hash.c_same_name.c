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
struct cache_entry {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ce_namelen (struct cache_entry const*) ; 
 int /*<<< orphan*/  memcmp (char const*,int /*<<< orphan*/ ,int) ; 
 int slow_same_name (char const*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int same_name(const struct cache_entry *ce, const char *name, int namelen, int icase)
{
	int len = ce_namelen(ce);

	/*
	 * Always do exact compare, even if we want a case-ignoring comparison;
	 * we do the quick exact one first, because it will be the common case.
	 */
	if (len == namelen && !memcmp(name, ce->name, len))
		return 1;

	if (!icase)
		return 0;

	return slow_same_name(name, namelen, ce->name, len);
}
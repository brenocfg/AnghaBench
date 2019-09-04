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
 int ce_namelen (struct cache_entry*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int different_name(struct cache_entry *ce, struct cache_entry *alias)
{
	int len = ce_namelen(ce);
	return ce_namelen(alias) != len || memcmp(ce->name, alias->name, len);
}
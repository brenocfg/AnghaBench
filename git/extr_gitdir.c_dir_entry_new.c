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
struct dir_entry {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLEX_ALLOC_MEM (struct dir_entry*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  name ; 

__attribute__((used)) static struct dir_entry *dir_entry_new(const char *pathname, int len)
{
	struct dir_entry *ent;

	FLEX_ALLOC_MEM(ent, name, pathname, len);
	ent->len = len;
	return ent;
}
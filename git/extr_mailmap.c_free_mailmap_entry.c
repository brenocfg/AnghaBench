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
struct TYPE_2__ {char const* nr; int strdup_strings; } ;
struct mailmap_entry {TYPE_1__ namemap; int /*<<< orphan*/  email; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_mm (char*,char const*,char const*) ; 
 char const* debug_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_mailmap_info ; 
 int /*<<< orphan*/  string_list_clear_func (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_mailmap_entry(void *p, const char *s)
{
	struct mailmap_entry *me = (struct mailmap_entry *)p;
	debug_mm("mailmap: removing entries for <%s>, with %d sub-entries\n",
		 s, me->namemap.nr);
	debug_mm("mailmap: - simple: '%s' <%s>\n",
		 debug_str(me->name), debug_str(me->email));

	free(me->name);
	free(me->email);

	me->namemap.strdup_strings = 1;
	string_list_clear_func(&me->namemap, free_mailmap_info);
}
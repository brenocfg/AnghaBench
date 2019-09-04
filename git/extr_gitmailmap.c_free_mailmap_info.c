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
struct mailmap_info {int /*<<< orphan*/  email; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_mm (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_mailmap_info(void *p, const char *s)
{
	struct mailmap_info *mi = (struct mailmap_info *)p;
	debug_mm("mailmap: -- complex: '%s' -> '%s' <%s>\n",
		 s, debug_str(mi->name), debug_str(mi->email));
	free(mi->name);
	free(mi->email);
}
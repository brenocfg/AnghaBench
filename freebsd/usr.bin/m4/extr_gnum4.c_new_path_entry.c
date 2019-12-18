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
struct path_entry {scalar_t__ next; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*) ; 
 struct path_entry* malloc (int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static struct path_entry *
new_path_entry(const char *dirname)
{
	struct path_entry *n;

	n = malloc(sizeof(struct path_entry));
	if (!n)
		errx(1, "out of memory");
	n->name = xstrdup(dirname);
	n->next = 0;
	return n;
}
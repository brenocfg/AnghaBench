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
struct packed_git {struct packed_git* next; int /*<<< orphan*/  pack_name; } ;
struct pack_list {int dummy; } ;

/* Variables and functions */
 struct pack_list* add_pack (struct packed_git*) ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 struct packed_git* get_all_packs (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static struct pack_list * add_pack_file(const char *filename)
{
	struct packed_git *p = get_all_packs(the_repository);

	if (strlen(filename) < 40)
		die("Bad pack filename: %s", filename);

	while (p) {
		if (strstr(p->pack_name, filename))
			return add_pack(p);
		p = p->next;
	}
	die("Filename %s not found in packed_git", filename);
}
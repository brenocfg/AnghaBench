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
struct packed_git {struct packed_git* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_pack (struct packed_git*) ; 
 struct packed_git* get_all_packs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void load_all(void)
{
	struct packed_git *p = get_all_packs(the_repository);

	while (p) {
		add_pack(p);
		p = p->next;
	}
}
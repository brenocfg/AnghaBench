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
struct patch {int /*<<< orphan*/  new_oid_prefix; int /*<<< orphan*/  old_oid_prefix; int /*<<< orphan*/  lines_deleted; int /*<<< orphan*/  lines_added; int /*<<< orphan*/  is_delete; int /*<<< orphan*/  is_new; int /*<<< orphan*/  old_mode; int /*<<< orphan*/  new_mode; int /*<<< orphan*/  old_name; int /*<<< orphan*/  new_name; struct fragment* fragments; struct patch* next; } ;
struct fragment {int /*<<< orphan*/  oldlines; int /*<<< orphan*/  newlines; int /*<<< orphan*/  oldpos; int /*<<< orphan*/  newpos; struct fragment* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reverse_patches(struct patch *p)
{
	for (; p; p = p->next) {
		struct fragment *frag = p->fragments;

		SWAP(p->new_name, p->old_name);
		SWAP(p->new_mode, p->old_mode);
		SWAP(p->is_new, p->is_delete);
		SWAP(p->lines_added, p->lines_deleted);
		SWAP(p->old_oid_prefix, p->new_oid_prefix);

		for (; frag; frag = frag->next) {
			SWAP(frag->newpos, frag->oldpos);
			SWAP(frag->newlines, frag->oldlines);
		}
	}
}
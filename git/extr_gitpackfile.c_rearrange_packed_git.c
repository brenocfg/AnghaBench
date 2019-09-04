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
struct repository {TYPE_1__* objects; } ;
struct TYPE_2__ {int /*<<< orphan*/  packed_git; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_next_packed_git ; 
 int /*<<< orphan*/  llist_mergesort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_next_packed_git ; 
 int /*<<< orphan*/  sort_pack ; 

__attribute__((used)) static void rearrange_packed_git(struct repository *r)
{
	r->objects->packed_git = llist_mergesort(
		r->objects->packed_git, get_next_packed_git,
		set_next_packed_git, sort_pack);
}
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
typedef  scalar_t__ time_t ;
struct pack_backend {int dummy; } ;
struct git_pack_entry {TYPE_1__* p; } ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb_backend ;
struct TYPE_2__ {scalar_t__ last_freshen; int /*<<< orphan*/  pack_name; } ;

/* Variables and functions */
 scalar_t__ FRESHEN_FREQUENCY ; 
 int git_futils_touch (int /*<<< orphan*/ ,scalar_t__*) ; 
 int pack_entry_find (struct git_pack_entry*,struct pack_backend*,int /*<<< orphan*/  const*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pack_backend__freshen(
	git_odb_backend *backend, const git_oid *oid)
{
	struct git_pack_entry e;
	time_t now;
	int error;

	if ((error = pack_entry_find(&e, (struct pack_backend *)backend, oid)) < 0)
		return error;

	now = time(NULL);

	if (e.p->last_freshen > now - FRESHEN_FREQUENCY)
		return 0;

	if ((error = git_futils_touch(e.p->pack_name, &now)) < 0)
		return error;

	e.p->last_freshen = now;
	return 0;
}
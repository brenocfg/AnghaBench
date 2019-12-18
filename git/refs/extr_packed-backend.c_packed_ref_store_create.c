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
struct ref_store {int dummy; } ;
struct packed_ref_store {unsigned int store_flags; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  base_ref_store_init (struct ref_store*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chdir_notify_reparent (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refs_be_packed ; 
 struct packed_ref_store* xcalloc (int,int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

struct ref_store *packed_ref_store_create(const char *path,
					  unsigned int store_flags)
{
	struct packed_ref_store *refs = xcalloc(1, sizeof(*refs));
	struct ref_store *ref_store = (struct ref_store *)refs;

	base_ref_store_init(ref_store, &refs_be_packed);
	refs->store_flags = store_flags;

	refs->path = xstrdup(path);
	chdir_notify_reparent("packed-refs", &refs->path);

	return ref_store;
}
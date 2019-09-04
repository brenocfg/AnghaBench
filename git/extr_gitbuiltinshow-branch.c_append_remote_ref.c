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
struct object_id {int dummy; } ;

/* Variables and functions */
 int append_ref (char const*,struct object_id const*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 int /*<<< orphan*/  oideq (struct object_id*,struct object_id const*) ; 
 int /*<<< orphan*/  starts_with (char const*,char*) ; 

__attribute__((used)) static int append_remote_ref(const char *refname, const struct object_id *oid,
			     int flag, void *cb_data)
{
	struct object_id tmp;
	int ofs = 13;
	if (!starts_with(refname, "refs/remotes/"))
		return 0;
	/* If both heads/foo and tags/foo exists, get_sha1 would
	 * get confused.
	 */
	if (get_oid(refname + ofs, &tmp) || !oideq(&tmp, oid))
		ofs = 5;
	return append_ref(refname + ofs, oid, 0);
}
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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 scalar_t__ get_oid (int /*<<< orphan*/ ,struct object_id*) ; 
 scalar_t__ is_null_oid (struct object_id const*) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  oidclr (struct object_id*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gitmodule_oid_from_commit(const struct object_id *treeish_name,
				     struct object_id *gitmodules_oid,
				     struct strbuf *rev)
{
	int ret = 0;

	if (is_null_oid(treeish_name)) {
		oidclr(gitmodules_oid);
		return 1;
	}

	strbuf_addf(rev, "%s:.gitmodules", oid_to_hex(treeish_name));
	if (get_oid(rev->buf, gitmodules_oid) >= 0)
		ret = 1;

	return ret;
}
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
struct strbuf {char* buf; } ;
struct ref_transaction {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int create_reflog_flag ; 
 int default_flags ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ is_null_oid (struct object_id*) ; 
 char const line_termination ; 
 int /*<<< orphan*/  msg ; 
 scalar_t__ parse_next_oid (struct strbuf*,char const**,struct object_id*,char*,char*,int /*<<< orphan*/ ) ; 
 char* parse_refname (struct strbuf*,char const**) ; 
 scalar_t__ ref_transaction_create (struct ref_transaction*,char*,struct object_id*,int,int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int update_flags ; 

__attribute__((used)) static const char *parse_cmd_create(struct ref_transaction *transaction,
				    struct strbuf *input, const char *next)
{
	struct strbuf err = STRBUF_INIT;
	char *refname;
	struct object_id new_oid;

	refname = parse_refname(input, &next);
	if (!refname)
		die("create: missing <ref>");

	if (parse_next_oid(input, &next, &new_oid, "create", refname, 0))
		die("create %s: missing <newvalue>", refname);

	if (is_null_oid(&new_oid))
		die("create %s: zero <newvalue>", refname);

	if (*next != line_termination)
		die("create %s: extra input: %s", refname, next);

	if (ref_transaction_create(transaction, refname, &new_oid,
				   update_flags | create_reflog_flag,
				   msg, &err))
		die("%s", err.buf);

	update_flags = default_flags;
	free(refname);
	strbuf_release(&err);

	return next;
}
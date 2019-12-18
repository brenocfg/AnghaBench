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
struct ref_transaction {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PARSE_SHA1_OLD ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  default_flags ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char const line_termination ; 
 int /*<<< orphan*/  oidclr (struct object_id*) ; 
 scalar_t__ parse_next_oid (struct strbuf*,char const**,struct object_id*,char*,char*,int /*<<< orphan*/ ) ; 
 char* parse_refname (struct strbuf*,char const**) ; 
 scalar_t__ ref_transaction_verify (struct ref_transaction*,char*,struct object_id*,int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  update_flags ; 

__attribute__((used)) static const char *parse_cmd_verify(struct ref_transaction *transaction,
				    struct strbuf *input, const char *next)
{
	struct strbuf err = STRBUF_INIT;
	char *refname;
	struct object_id old_oid;

	refname = parse_refname(input, &next);
	if (!refname)
		die("verify: missing <ref>");

	if (parse_next_oid(input, &next, &old_oid, "verify", refname,
			   PARSE_SHA1_OLD))
		oidclr(&old_oid);

	if (*next != line_termination)
		die("verify %s: extra input: %s", refname, next);

	if (ref_transaction_verify(transaction, refname, &old_oid,
				   update_flags, &err))
		die("%s", err.buf);

	update_flags = default_flags;
	free(refname);
	strbuf_release(&err);

	return next;
}
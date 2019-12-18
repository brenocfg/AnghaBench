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
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ check_refname_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_replace_ref_base ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id*) ; 
 int /*<<< orphan*/  oidclr (struct object_id*) ; 
 scalar_t__ read_ref (int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

__attribute__((used)) static int check_ref_valid(struct object_id *object,
			    struct object_id *prev,
			    struct strbuf *ref,
			    int force)
{
	strbuf_reset(ref);
	strbuf_addf(ref, "%s%s", git_replace_ref_base, oid_to_hex(object));
	if (check_refname_format(ref->buf, 0))
		return error(_("'%s' is not a valid ref name"), ref->buf);

	if (read_ref(ref->buf, prev))
		oidclr(prev);
	else if (!force)
		return error(_("replace ref '%s' already exists"), ref->buf);
	return 0;
}
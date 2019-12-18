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
struct strbuf {int /*<<< orphan*/  buf; scalar_t__ len; } ;
struct ref_store {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int arg_flags (int /*<<< orphan*/ ,char*) ; 
 char* notnull (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 
 int refs_create_reflog (struct ref_store*,char const*,int,struct strbuf*) ; 

__attribute__((used)) static int cmd_create_reflog(struct ref_store *refs, const char **argv)
{
	const char *refname = notnull(*argv++, "refname");
	int force_create = arg_flags(*argv++, "force-create");
	struct strbuf err = STRBUF_INIT;
	int ret;

	ret = refs_create_reflog(refs, refname, force_create, &err);
	if (err.len)
		puts(err.buf);
	return ret;
}
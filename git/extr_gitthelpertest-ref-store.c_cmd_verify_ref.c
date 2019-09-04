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
 char* notnull (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 
 int refs_verify_refname_available (struct ref_store*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct strbuf*) ; 

__attribute__((used)) static int cmd_verify_ref(struct ref_store *refs, const char **argv)
{
	const char *refname = notnull(*argv++, "refname");
	struct strbuf err = STRBUF_INIT;
	int ret;

	ret = refs_verify_refname_available(refs, refname, NULL, NULL, &err);
	if (err.len)
		puts(err.buf);
	return ret;
}
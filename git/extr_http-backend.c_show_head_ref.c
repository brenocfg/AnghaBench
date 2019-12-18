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
struct strbuf {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int REF_ISSYMREF ; 
 int /*<<< orphan*/  RESOLVE_REF_READING ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 char* resolve_ref_unsafe (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strip_namespace (char const*) ; 

__attribute__((used)) static int show_head_ref(const char *refname, const struct object_id *oid,
			 int flag, void *cb_data)
{
	struct strbuf *buf = cb_data;

	if (flag & REF_ISSYMREF) {
		const char *target = resolve_ref_unsafe(refname,
							RESOLVE_REF_READING,
							NULL, NULL);

		if (target)
			strbuf_addf(buf, "ref: %s\n", strip_namespace(target));
	} else {
		strbuf_addf(buf, "%s\n", oid_to_hex(oid));
	}

	return 0;
}
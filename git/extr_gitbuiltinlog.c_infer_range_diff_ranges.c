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
struct strbuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 char const* oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,char const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strstr (char const*,char*) ; 

__attribute__((used)) static void infer_range_diff_ranges(struct strbuf *r1,
				    struct strbuf *r2,
				    const char *prev,
				    struct commit *origin,
				    struct commit *head)
{
	const char *head_oid = oid_to_hex(&head->object.oid);

	if (!strstr(prev, "..")) {
		strbuf_addf(r1, "%s..%s", head_oid, prev);
		strbuf_addf(r2, "%s..%s", prev, head_oid);
	} else if (!origin) {
		die(_("failed to infer range-diff ranges"));
	} else {
		strbuf_addstr(r1, prev);
		strbuf_addf(r2, "%s..%s",
			    oid_to_hex(&origin->object.oid), head_oid);
	}
}
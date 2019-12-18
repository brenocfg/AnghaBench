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
struct packed_git {int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 struct packed_git** all_packs ; 
 int /*<<< orphan*/  odb_pack_name (struct strbuf*,int /*<<< orphan*/ ,char*) ; 
 int pack_id ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  unlink_or_warn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unkeep_all_packs(void)
{
	struct strbuf name = STRBUF_INIT;
	int k;

	for (k = 0; k < pack_id; k++) {
		struct packed_git *p = all_packs[k];
		odb_pack_name(&name, p->hash, "keep");
		unlink_or_warn(name.buf);
	}
	strbuf_release(&name);
}
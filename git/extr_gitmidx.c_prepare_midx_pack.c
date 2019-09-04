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
typedef  size_t uint32_t ;
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct multi_pack_index {size_t num_packs; int /*<<< orphan*/ * packs; int /*<<< orphan*/  local; int /*<<< orphan*/ * pack_names; int /*<<< orphan*/  object_dir; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_packed_git (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

int prepare_midx_pack(struct multi_pack_index *m, uint32_t pack_int_id)
{
	struct strbuf pack_name = STRBUF_INIT;

	if (pack_int_id >= m->num_packs)
		die(_("bad pack-int-id: %u (%u total packs)"),
		    pack_int_id, m->num_packs);

	if (m->packs[pack_int_id])
		return 0;

	strbuf_addf(&pack_name, "%s/pack/%s", m->object_dir,
		    m->pack_names[pack_int_id]);

	m->packs[pack_int_id] = add_packed_git(pack_name.buf, pack_name.len, m->local);
	strbuf_release(&pack_name);
	return !m->packs[pack_int_id];
}
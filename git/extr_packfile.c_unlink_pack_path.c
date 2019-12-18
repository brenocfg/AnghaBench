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
struct strbuf {size_t len; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  F_OK ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  access (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,size_t) ; 
 int /*<<< orphan*/  strip_suffix_mem (int /*<<< orphan*/ ,size_t*,char*) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

void unlink_pack_path(const char *pack_name, int force_delete)
{
	static const char *exts[] = {".pack", ".idx", ".keep", ".bitmap", ".promisor"};
	int i;
	struct strbuf buf = STRBUF_INIT;
	size_t plen;

	strbuf_addstr(&buf, pack_name);
	strip_suffix_mem(buf.buf, &buf.len, ".pack");
	plen = buf.len;

	if (!force_delete) {
		strbuf_addstr(&buf, ".keep");
		if (!access(buf.buf, F_OK)) {
			strbuf_release(&buf);
			return;
		}
	}

	for (i = 0; i < ARRAY_SIZE(exts); i++) {
		strbuf_setlen(&buf, plen);
		strbuf_addstr(&buf, exts[i]);
		unlink(buf.buf);
	}

	strbuf_release(&buf);
}
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
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,char const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,size_t) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remove_redundant_pack(const char *dir_name, const char *base_name)
{
	const char *exts[] = {".pack", ".idx", ".keep", ".bitmap", ".promisor"};
	int i;
	struct strbuf buf = STRBUF_INIT;
	size_t plen;

	strbuf_addf(&buf, "%s/%s", dir_name, base_name);
	plen = buf.len;

	for (i = 0; i < ARRAY_SIZE(exts); i++) {
		strbuf_setlen(&buf, plen);
		strbuf_addstr(&buf, exts[i]);
		unlink(buf.buf);
	}
	strbuf_release(&buf);
}
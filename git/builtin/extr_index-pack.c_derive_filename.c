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
struct strbuf {char const* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,size_t) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strip_suffix (char const*,char*,size_t*) ; 

__attribute__((used)) static const char *derive_filename(const char *pack_name, const char *suffix,
				   struct strbuf *buf)
{
	size_t len;
	if (!strip_suffix(pack_name, ".pack", &len))
		die(_("packfile name '%s' does not end with '.pack'"),
		    pack_name);
	strbuf_add(buf, pack_name, len);
	strbuf_addch(buf, '.');
	strbuf_addstr(buf, suffix);
	return buf->buf;
}
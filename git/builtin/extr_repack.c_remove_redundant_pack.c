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

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  unlink_pack_path (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void remove_redundant_pack(const char *dir_name, const char *base_name)
{
	struct strbuf buf = STRBUF_INIT;
	strbuf_addf(&buf, "%s/%s.pack", dir_name, base_name);
	unlink_pack_path(buf.buf, 1);
	strbuf_release(&buf);
}
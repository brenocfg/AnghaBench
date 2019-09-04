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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 char* gather_convert_stats_ascii (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strbuf_read_file (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

const char *get_wt_convert_stats_ascii(const char *path)
{
	const char *ret = "";
	struct strbuf sb = STRBUF_INIT;
	if (strbuf_read_file(&sb, path, 0) >= 0)
		ret = gather_convert_stats_ascii(sb.buf, sb.len);
	strbuf_release(&sb);
	return ret;
}
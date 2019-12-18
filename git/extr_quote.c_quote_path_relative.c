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
struct strbuf {char* buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  quote_c_style_counted (char const*,int /*<<< orphan*/ ,struct strbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* relative_path (char const*,char const*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

char *quote_path_relative(const char *in, const char *prefix,
			  struct strbuf *out)
{
	struct strbuf sb = STRBUF_INIT;
	const char *rel = relative_path(in, prefix, &sb);
	strbuf_reset(out);
	quote_c_style_counted(rel, strlen(rel), out, NULL, 0);
	strbuf_release(&sb);

	return out->buf;
}
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
struct strbuf {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf const*) ; 
 int /*<<< orphan*/  strbuf_init (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 struct strbuf* xmalloc (int) ; 

__attribute__((used)) static void handle_header(struct strbuf **out, const struct strbuf *line)
{
	if (!*out) {
		*out = xmalloc(sizeof(struct strbuf));
		strbuf_init(*out, line->len);
	} else
		strbuf_reset(*out);

	strbuf_addbuf(*out, line);
}
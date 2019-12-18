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
typedef  char u_char ;
struct sbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,char const) ; 
 int /*<<< orphan*/  sbuf_putc (struct sbuf*,char const) ; 

void
g_conf_cat_escaped(struct sbuf *sb, const char *buf)
{
	const u_char *c;

	for (c = buf; *c != '\0'; c++) {
		if (*c == '&' || *c == '<' || *c == '>' ||
		    *c == '\'' || *c == '"' || *c > 0x7e)
			sbuf_printf(sb, "&#x%X;", *c);
		else if (*c == '\t' || *c == '\n' || *c == '\r' || *c > 0x1f)
			sbuf_putc(sb, *c);
		else
			sbuf_putc(sb, '?');
	}
}
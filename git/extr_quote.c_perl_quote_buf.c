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
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char const) ; 

void perl_quote_buf(struct strbuf *sb, const char *src)
{
	const char sq = '\'';
	const char bq = '\\';
	char c;

	strbuf_addch(sb, sq);
	while ((c = *src++)) {
		if (c == sq || c == bq)
			strbuf_addch(sb, bq);
		strbuf_addch(sb, c);
	}
	strbuf_addch(sb, sq);
}
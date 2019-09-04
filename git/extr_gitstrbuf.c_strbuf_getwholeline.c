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
struct strbuf {int* buf; size_t len; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flockfile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  funlockfile (int /*<<< orphan*/ *) ; 
 int getc_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_avail (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_grow (struct strbuf*,int) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

int strbuf_getwholeline(struct strbuf *sb, FILE *fp, int term)
{
	int ch;

	if (feof(fp))
		return EOF;

	strbuf_reset(sb);
	flockfile(fp);
	while ((ch = getc_unlocked(fp)) != EOF) {
		if (!strbuf_avail(sb))
			strbuf_grow(sb, 1);
		sb->buf[sb->len++] = ch;
		if (ch == term)
			break;
	}
	funlockfile(fp);
	if (ch == EOF && sb->len == 0)
		return EOF;

	sb->buf[sb->len] = '\0';
	return 0;
}
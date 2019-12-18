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
struct strbuf {char* buf; int len; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 scalar_t__ strbuf_getwholeline (struct strbuf*,int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 

int strbuf_getline(struct strbuf *sb, FILE *fp)
{
	if (strbuf_getwholeline(sb, fp, '\n'))
		return EOF;
	if (sb->buf[sb->len - 1] == '\n') {
		strbuf_setlen(sb, sb->len - 1);
		if (sb->len && sb->buf[sb->len - 1] == '\r')
			strbuf_setlen(sb, sb->len - 1);
	}
	return 0;
}
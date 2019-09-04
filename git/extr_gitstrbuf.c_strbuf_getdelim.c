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
struct strbuf {int* buf; int len; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 scalar_t__ strbuf_getwholeline (struct strbuf*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 

__attribute__((used)) static int strbuf_getdelim(struct strbuf *sb, FILE *fp, int term)
{
	if (strbuf_getwholeline(sb, fp, term))
		return EOF;
	if (sb->buf[sb->len - 1] == term)
		strbuf_setlen(sb, sb->len - 1);
	return 0;
}
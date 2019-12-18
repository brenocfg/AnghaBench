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
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 

__attribute__((used)) static void add_line_count(struct strbuf *out, int count)
{
	switch (count) {
	case 0:
		strbuf_addstr(out, "0,0");
		break;
	case 1:
		strbuf_addstr(out, "1");
		break;
	default:
		strbuf_addf(out, "1,%d", count);
		break;
	}
}
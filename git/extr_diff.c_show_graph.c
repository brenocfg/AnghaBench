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
 int /*<<< orphan*/  strbuf_addchars (struct strbuf*,char,int) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 

__attribute__((used)) static void show_graph(struct strbuf *out, char ch, int cnt,
		       const char *set, const char *reset)
{
	if (cnt <= 0)
		return;
	strbuf_addstr(out, set);
	strbuf_addchars(out, ch, cnt);
	strbuf_addstr(out, reset);
}
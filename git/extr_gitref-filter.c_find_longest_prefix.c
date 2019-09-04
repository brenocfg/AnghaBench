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
 int /*<<< orphan*/  is_glob_special (char const) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 

__attribute__((used)) static void find_longest_prefix(struct strbuf *out, const char *pattern)
{
	const char *p;

	for (p = pattern; *p && !is_glob_special(*p); p++)
		;

	strbuf_add(out, pattern, p - pattern);
}
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
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,unsigned int) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int,char const*) ; 
 int /*<<< orphan*/  strbuf_grow (struct strbuf*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void strbuf_append_ext_header(struct strbuf *sb, const char *keyword,
				     const char *value, unsigned int valuelen)
{
	int len, tmp;

	/* "%u %s=%s\n" */
	len = 1 + 1 + strlen(keyword) + 1 + valuelen + 1;
	for (tmp = len; tmp > 9; tmp /= 10)
		len++;

	strbuf_grow(sb, len);
	strbuf_addf(sb, "%u %s=", len, keyword);
	strbuf_add(sb, value, valuelen);
	strbuf_addch(sb, '\n');
}
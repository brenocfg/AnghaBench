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
typedef  scalar_t__ (* char_predicate ) (char) ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,unsigned char) ; 
 int /*<<< orphan*/  strbuf_grow (struct strbuf*,size_t) ; 

__attribute__((used)) static void strbuf_add_urlencode(struct strbuf *sb, const char *s, size_t len,
				 char_predicate allow_unencoded_fn)
{
	strbuf_grow(sb, len);
	while (len--) {
		char ch = *s++;
		if (allow_unencoded_fn(ch))
			strbuf_addch(sb, ch);
		else
			strbuf_addf(sb, "%%%02x", (unsigned char)ch);
	}
}
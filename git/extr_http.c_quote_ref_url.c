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
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  end_url_with_slash (struct strbuf*,char const*) ; 
 scalar_t__ needs_quote (int) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char const) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *quote_ref_url(const char *base, const char *ref)
{
	struct strbuf buf = STRBUF_INIT;
	const char *cp;
	int ch;

	end_url_with_slash(&buf, base);

	for (cp = ref; (ch = *cp) != 0; cp++)
		if (needs_quote(ch))
			strbuf_addf(&buf, "%%%02x", ch);
		else
			strbuf_addch(&buf, *cp);

	return strbuf_detach(&buf, NULL);
}
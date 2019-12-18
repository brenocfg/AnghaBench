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
struct strbuf {char* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESERVED_NON_WS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,int /*<<< orphan*/ ,char const) ; 
 scalar_t__ strchr (int /*<<< orphan*/ ,char const) ; 

__attribute__((used)) static int has_reserved_character(
	struct strbuf *sub_spec, struct strbuf *errbuf)
{
	const char *c = sub_spec->buf;
	while (*c) {
		if (*c <= ' ' || strchr(RESERVED_NON_WS, *c)) {
			strbuf_addf(
				errbuf,
				_("must escape char in sub-filter-spec: '%c'"),
				*c);
			return 1;
		}
		c++;
	}

	return 0;
}
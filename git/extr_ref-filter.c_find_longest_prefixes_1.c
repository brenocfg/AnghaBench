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
struct string_list {int dummy; } ;
struct strbuf {size_t len; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 scalar_t__ is_glob_special (char) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char const) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void find_longest_prefixes_1(struct string_list *out,
				  struct strbuf *prefix,
				  const char **patterns, size_t nr)
{
	size_t i;

	for (i = 0; i < nr; i++) {
		char c = patterns[i][prefix->len];
		if (!c || is_glob_special(c)) {
			string_list_append(out, prefix->buf);
			return;
		}
	}

	i = 0;
	while (i < nr) {
		size_t end;

		/*
		* Set "end" to the index of the element _after_ the last one
		* in our group.
		*/
		for (end = i + 1; end < nr; end++) {
			if (patterns[i][prefix->len] != patterns[end][prefix->len])
				break;
		}

		strbuf_addch(prefix, patterns[i][prefix->len]);
		find_longest_prefixes_1(out, prefix, patterns + i, end - i);
		strbuf_setlen(prefix, prefix->len - 1);

		i = end;
	}
}
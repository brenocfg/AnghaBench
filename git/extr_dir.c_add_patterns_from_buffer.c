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
struct pattern_list {char* filebuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_pattern (char*,char const*,int,struct pattern_list*,int) ; 
 scalar_t__ skip_utf8_bom (char**,size_t) ; 
 int /*<<< orphan*/  trim_trailing_spaces (char*) ; 

__attribute__((used)) static int add_patterns_from_buffer(char *buf, size_t size,
				    const char *base, int baselen,
				    struct pattern_list *pl)
{
	int i, lineno = 1;
	char *entry;

	pl->filebuf = buf;

	if (skip_utf8_bom(&buf, size))
		size -= buf - pl->filebuf;

	entry = buf;

	for (i = 0; i < size; i++) {
		if (buf[i] == '\n') {
			if (entry != buf + i && entry[0] != '#') {
				buf[i - (i && buf[i-1] == '\r')] = 0;
				trim_trailing_spaces(entry);
				add_pattern(entry, base, baselen, pl, lineno);
			}
			lineno++;
			entry = buf + i + 1;
		}
	}
	return 0;
}
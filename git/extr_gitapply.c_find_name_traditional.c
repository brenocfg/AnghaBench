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
struct apply_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TERM_TAB ; 
 size_t diff_timestamp_len (char const*,size_t) ; 
 char* find_name_common (struct apply_state*,char const*,char*,int,char const*,int /*<<< orphan*/ ) ; 
 char* find_name_gnu (struct apply_state*,char const*,int) ; 
 char const* strchrnul (char const*,char) ; 

__attribute__((used)) static char *find_name_traditional(struct apply_state *state,
				   const char *line,
				   char *def,
				   int p_value)
{
	size_t len;
	size_t date_len;

	if (*line == '"') {
		char *name = find_name_gnu(state, line, p_value);
		if (name)
			return name;
	}

	len = strchrnul(line, '\n') - line;
	date_len = diff_timestamp_len(line, len);
	if (!date_len)
		return find_name_common(state, line, def, p_value, NULL, TERM_TAB);
	len -= date_len;

	return find_name_common(state, line, def, p_value, line + len, 0);
}
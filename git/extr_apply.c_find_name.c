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
 char* find_name_common (struct strbuf*,char const*,char*,int,int /*<<< orphan*/ *,int) ; 
 char* find_name_gnu (struct strbuf*,char const*,int) ; 

__attribute__((used)) static char *find_name(struct strbuf *root,
		       const char *line,
		       char *def,
		       int p_value,
		       int terminate)
{
	if (*line == '"') {
		char *name = find_name_gnu(root, line, p_value);
		if (name)
			return name;
	}

	return find_name_common(root, line, def, p_value, NULL, terminate);
}
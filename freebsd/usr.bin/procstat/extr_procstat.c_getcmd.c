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
struct procstat_cmd {int cmp; char const* command; } ;

/* Variables and functions */
 int PS_CMP_PLURAL ; 
 int PS_CMP_SUBSTR ; 
 struct procstat_cmd* cmd_table ; 
 size_t nitems (struct procstat_cmd*) ; 
 int strcasecmp (char const*,char*) ; 
 int strlen (char const*) ; 
 int strncasecmp (char const*,char const*,size_t) ; 

__attribute__((used)) static const struct procstat_cmd *
getcmd(const char *str)
{
	const struct procstat_cmd *cmd;
	size_t i, l;
	int cmp, s;

	if (str == NULL)
		return (NULL);
	cmd = NULL;
	if ((l = strlen(str)) == 0)
		return (getcmd("basic"));
	s = l > 1 && strcasecmp(str + l - 1, "s") == 0;
	for (i = 0; i < nitems(cmd_table); i++) {
		/*
		 * After the first match substring matches are disabled,
		 * allowing subsequent full matches to take precedence.
		 */
		if (cmd == NULL && (cmd_table[i].cmp & PS_CMP_SUBSTR))
			cmp = strncasecmp(str, cmd_table[i].command, l -
			    ((cmd_table[i].cmp & PS_CMP_PLURAL) && s ? 1 : 0));
		else if ((cmd_table[i].cmp & PS_CMP_PLURAL) && s &&
		    l == strlen(cmd_table[i].command) + 1)
			cmp = strncasecmp(str, cmd_table[i].command, l - 1);
		else
			cmp = strcasecmp(str, cmd_table[i].command);
		if (cmp == 0)
			cmd = &cmd_table[i];
	}
	return (cmd);
}
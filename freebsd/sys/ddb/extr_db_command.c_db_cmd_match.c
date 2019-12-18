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
struct command {char* name; } ;

/* Variables and functions */
 int CMD_AMBIGUOUS ; 
 int CMD_FOUND ; 
 int CMD_UNIQUE ; 

__attribute__((used)) static void
db_cmd_match(char *name, struct command *cmd, struct command **cmdp,
    int *resultp)
{
	char *lp, *rp;
	int c;

	lp = name;
	rp = cmd->name;
	while ((c = *lp) == *rp) {
		if (c == 0) {
			/* complete match */
			*cmdp = cmd;
			*resultp = CMD_UNIQUE;
			return;
		}
		lp++;
		rp++;
	}
	if (c == 0) {
		/* end of name, not end of command -
		   partial match */
		if (*resultp == CMD_FOUND) {
			*resultp = CMD_AMBIGUOUS;
			/* but keep looking for a full match -
			   this lets us match single letters */
		} else {
			*cmdp = cmd;
			*resultp = CMD_FOUND;
		}
	}
}
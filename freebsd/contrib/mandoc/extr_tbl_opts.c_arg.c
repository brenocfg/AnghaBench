#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char tab; char decimal; } ;
struct tbl_node {TYPE_1__ opts; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  KEY_DELIM 131 
#define  KEY_DPOINT 130 
#define  KEY_LINESIZE 129 
#define  KEY_TAB 128 
 int /*<<< orphan*/  MANDOCERR_TBLOPT_ARGSZ ; 
 int /*<<< orphan*/  MANDOCERR_TBLOPT_EQN ; 
 int /*<<< orphan*/  MANDOCERR_TBLOPT_NOARG ; 
 int /*<<< orphan*/  abort () ; 
 TYPE_2__* keys ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int,int,char*,int,...) ; 

__attribute__((used)) static void
arg(struct tbl_node *tbl, int ln, const char *p, int *pos, int key)
{
	int		 len, want;

	while (p[*pos] == ' ' || p[*pos] == '\t')
		(*pos)++;

	/* Arguments are enclosed in parentheses. */

	len = 0;
	if (p[*pos] == '(') {
		(*pos)++;
		while (p[*pos + len] != ')')
			len++;
	}

	switch (key) {
	case KEY_DELIM:
		mandoc_msg(MANDOCERR_TBLOPT_EQN,
		    ln, *pos, "%.*s", len, p + *pos);
		want = 2;
		break;
	case KEY_TAB:
		want = 1;
		if (len == want)
			tbl->opts.tab = p[*pos];
		break;
	case KEY_LINESIZE:
		want = 0;
		break;
	case KEY_DPOINT:
		want = 1;
		if (len == want)
			tbl->opts.decimal = p[*pos];
		break;
	default:
		abort();
	}

	if (len == 0)
		mandoc_msg(MANDOCERR_TBLOPT_NOARG, ln, *pos,
		    "%s", keys[key].name);
	else if (want && len != want)
		mandoc_msg(MANDOCERR_TBLOPT_ARGSZ, ln, *pos,
		    "%s want %d have %d", keys[key].name, want, len);

	*pos += len;
	if (p[*pos] == ')')
		(*pos)++;
}
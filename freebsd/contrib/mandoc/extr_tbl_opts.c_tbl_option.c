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
struct TYPE_3__ {int opts; } ;
struct tbl_node {TYPE_1__ opts; } ;
struct TYPE_4__ {char* name; int key; } ;

/* Variables and functions */
 int KEY_MAXKEYS ; 
 int /*<<< orphan*/  MANDOCERR_TBLOPT_ALPHA ; 
 int /*<<< orphan*/  MANDOCERR_TBLOPT_BAD ; 
 int /*<<< orphan*/  arg (struct tbl_node*,int,char const*,int*,int) ; 
 scalar_t__ isalpha (unsigned char) ; 
 TYPE_2__* keys ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int,int,char*,char const,...) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 

void
tbl_option(struct tbl_node *tbl, int ln, const char *p, int *offs)
{
	int		 i, pos, len;

	pos = *offs;
	for (;;) {
		while (p[pos] == ' ' || p[pos] == '\t' || p[pos] == ',')
			pos++;

		if (p[pos] == ';') {
			*offs = pos + 1;
			return;
		}

		/* Parse one option name. */

		len = 0;
		while (isalpha((unsigned char)p[pos + len]))
			len++;

		if (len == 0) {
			mandoc_msg(MANDOCERR_TBLOPT_ALPHA,
			    ln, pos, "%c", p[pos]);
			pos++;
			continue;
		}

		/* Look up the option name. */

		i = 0;
		while (i < KEY_MAXKEYS &&
		    (strncasecmp(p + pos, keys[i].name, len) ||
		     keys[i].name[len] != '\0'))
			i++;

		if (i == KEY_MAXKEYS) {
			mandoc_msg(MANDOCERR_TBLOPT_BAD,
			    ln, pos, "%.*s", len, p + pos);
			pos += len;
			continue;
		}

		/* Handle the option. */

		pos += len;
		if (keys[i].key)
			tbl->opts.opts |= keys[i].key;
		else
			arg(tbl, ln, p, &pos, i);
	}
}
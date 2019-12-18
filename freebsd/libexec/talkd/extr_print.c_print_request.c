#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tbuf ;
struct TYPE_3__ {int type; int /*<<< orphan*/  r_tty; int /*<<< orphan*/  r_name; int /*<<< orphan*/  l_name; scalar_t__ id_num; } ;
typedef  TYPE_1__ CTL_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int NTYPES ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char const*,char const*,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char** types ; 

void
print_request(const char *cp, CTL_MSG *mp)
{
	const char *tp;
	char tbuf[80];

	if (mp->type > NTYPES) {
		(void)snprintf(tbuf, sizeof(tbuf), "type %d", mp->type);
		tp = tbuf;
	} else
		tp = types[mp->type];
	syslog(LOG_DEBUG, "%s: %s: id %lu, l_user %s, r_user %s, r_tty %s",
	    cp, tp, (long)mp->id_num, mp->l_name, mp->r_name, mp->r_tty);
}
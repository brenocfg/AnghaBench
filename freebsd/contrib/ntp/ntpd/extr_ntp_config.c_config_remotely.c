#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sockaddr_u ;
typedef  int /*<<< orphan*/  origin ;
struct TYPE_6__ {int /*<<< orphan*/  s; } ;
struct TYPE_5__ {TYPE_2__ value; int /*<<< orphan*/  attr; } ;
struct TYPE_7__ {TYPE_1__ source; int /*<<< orphan*/  timestamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_SOURCE_NTPQ ; 
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_3__ cfgt ; 
 int /*<<< orphan*/  estrdup (char*) ; 
 int /*<<< orphan*/  init_syntax_tree (TYPE_3__*) ; 
 int /*<<< orphan*/  lex_drop_stack () ; 
 int /*<<< orphan*/  lex_init_stack (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  save_and_apply_config_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 char* stoa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yyparse () ; 

void
config_remotely(
	sockaddr_u *	remote_addr
	)
{
	char origin[128];

	snprintf(origin, sizeof(origin), "remote config from %s",
		 stoa(remote_addr));
	lex_init_stack(origin, NULL); /* no checking needed... */
	init_syntax_tree(&cfgt);
	yyparse();
	lex_drop_stack();

	cfgt.source.attr = CONF_SOURCE_NTPQ;
	cfgt.timestamp = time(NULL);
	cfgt.source.value.s = estrdup(stoa(remote_addr));

	DPRINTF(1, ("Finished Parsing!!\n"));

	save_and_apply_config_tree(FALSE);
}
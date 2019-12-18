#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* pw; int /*<<< orphan*/  self; } ;
struct TYPE_4__ {int /*<<< orphan*/  pw_name; } ;
typedef  TYPE_2__ Session ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  session_tty_list () ; 
 int /*<<< orphan*/  setproctitle (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
session_proctitle(Session *s)
{
	if (s->pw == NULL)
		error("no user for session %d", s->self);
	else
		setproctitle("%s@%s", s->pw->pw_name, session_tty_list());
}
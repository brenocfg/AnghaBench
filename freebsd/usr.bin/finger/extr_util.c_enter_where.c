#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tv_sec; } ;
struct utmpx {TYPE_1__ ut_tv; int /*<<< orphan*/  ut_host; int /*<<< orphan*/  ut_line; } ;
struct TYPE_6__ {int /*<<< orphan*/  loginat; int /*<<< orphan*/  host; int /*<<< orphan*/  tty; int /*<<< orphan*/  info; } ;
typedef  TYPE_2__ WHERE ;
typedef  int /*<<< orphan*/  PERSON ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGEDIN ; 
 int /*<<< orphan*/  find_idle_and_ttywrite (TYPE_2__*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* walloc (int /*<<< orphan*/ *) ; 

void
enter_where(struct utmpx *ut, PERSON *pn)
{
	WHERE *w;

	w = walloc(pn);
	w->info = LOGGEDIN;
	strcpy(w->tty, ut->ut_line);
	strcpy(w->host, ut->ut_host);
	w->loginat = ut->ut_tv.tv_sec;
	find_idle_and_ttywrite(w);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_2__ {scalar_t__ tv_sec; } ;
struct utmpx {TYPE_1__ ut_tv; } ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  ct ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 char* ctf (char*) ; 
 int /*<<< orphan*/  doentry (struct utmpx*) ; 
 int /*<<< orphan*/  endutxent () ; 
 char* file ; 
 int /*<<< orphan*/  free (struct utmpx*) ; 
 struct utmpx* getutxent () ; 
 int /*<<< orphan*/  idlist ; 
 struct tm* localtime (scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (struct utmpx*,struct utmpx*,int) ; 
 struct utmpx* realloc (struct utmpx*,unsigned int) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 
 int /*<<< orphan*/  xo_attr (char*,char*,unsigned long) ; 
 int /*<<< orphan*/  xo_close_container (char*) ; 
 int /*<<< orphan*/  xo_close_list (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,char*) ; 
 int /*<<< orphan*/  xo_err (int,char*) ; 
 int /*<<< orphan*/  xo_open_container (char*) ; 
 int /*<<< orphan*/  xo_open_list (char*) ; 

__attribute__((used)) static void
wtmp(void)
{
	struct utmpx *buf = NULL;
	struct utmpx *ut;
	static unsigned int amount = 0;
	time_t t;
	char ct[80];
	struct tm *tm;

	SLIST_INIT(&idlist);
	(void)time(&t);

	xo_open_container("last-information");

	/* Load the last entries from the file. */
	while ((ut = getutxent()) != NULL) {
		if (amount % 128 == 0) {
			buf = realloc(buf, (amount + 128) * sizeof *ut);
			if (buf == NULL)
				xo_err(1, "realloc");
		}
		memcpy(&buf[amount++], ut, sizeof *ut);
		if (t > ut->ut_tv.tv_sec)
			t = ut->ut_tv.tv_sec;
	}
	endutxent();

	/* Display them in reverse order. */
	xo_open_list("last");
	while (amount > 0)
		doentry(&buf[--amount]);
	xo_close_list("last");
	free(buf);
	tm = localtime(&t);
	(void) strftime(ct, sizeof(ct), "%+", tm);
	xo_emit("\n{:utxdb/%s}", (file == NULL) ? "utx.log" : file);
	xo_attr("seconds", "%lu", (unsigned long) t);
	xo_emit(ctf(" begins {:begins/%s}\n"), ct);
	xo_close_container("last-information");
}
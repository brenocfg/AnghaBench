#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct userinfo {int ui_calls; int ui_utime; int ui_stime; int ui_io; double ui_mem; int /*<<< orphan*/  ui_uid; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ DBT ;

/* Variables and functions */
 int DB_SEQ (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* MAXLOGNAME ; 
 int /*<<< orphan*/  R_FIRST ; 
 int /*<<< orphan*/  R_NEXT ; 
 scalar_t__ dflag ; 
 scalar_t__ kflag ; 
 int /*<<< orphan*/  memcpy (struct userinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  user_from_uid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usracct_db ; 
 int /*<<< orphan*/  warn (char*) ; 

void
usracct_print(void)
{
	DBT key, data;
	struct userinfo uistore, *ui = &uistore;
	double t;
	int rv;

	rv = DB_SEQ(usracct_db, &key, &data, R_FIRST);
	if (rv < 0)
		warn("retrieving user accounting stats");

	while (rv == 0) {
		memcpy(ui, data.data, sizeof(struct userinfo));

		printf("%-*s %9ju ", MAXLOGNAME - 1,
		    user_from_uid(ui->ui_uid, 0), (uintmax_t)ui->ui_calls);

		t = (ui->ui_utime + ui->ui_stime) / 1000000;
		if (t < 0.000001)		/* kill divide by zero */
			t = 0.000001;

		printf("%12.2f%s ", t / 60.0, "cpu");

		/* ui->ui_calls is always != 0 */
		if (dflag)
			printf("%12.0f%s",
			    ui->ui_io / ui->ui_calls, "avio");
		else
			printf("%12.0f%s", ui->ui_io, "tio");

		/* t is always >= 0.000001; see above. */
		if (kflag)
			printf("%12.0f%s", ui->ui_mem / t, "k");
		else
			printf("%12.0f%s", ui->ui_mem, "k*sec");

		printf("\n");

		rv = DB_SEQ(usracct_db, &key, &data, R_NEXT);
		if (rv < 0)
			warn("retrieving user accounting stats");
	}
}
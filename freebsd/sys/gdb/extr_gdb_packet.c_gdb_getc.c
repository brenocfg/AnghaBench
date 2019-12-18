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
struct TYPE_2__ {int (* gdb_getc ) () ;int gdb_dbfeatures; int /*<<< orphan*/  (* gdb_term ) () ;} ;

/* Variables and functions */
 int CTRL (char) ; 
 int GDB_DBGP_FEAT_WANTTERM ; 
 TYPE_1__* gdb_cur ; 
 scalar_t__ kdb_dbbe_select (char*) ; 
 int /*<<< orphan*/  kdb_reenter () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

__attribute__((used)) static int
gdb_getc(void)
{
	int c;

	do
		c = gdb_cur->gdb_getc();
	while (c == -1);

	if (c == CTRL('C')) {
		printf("Received ^C; trying to switch back to ddb.\n");

		if (gdb_cur->gdb_dbfeatures & GDB_DBGP_FEAT_WANTTERM)
			gdb_cur->gdb_term();

		if (kdb_dbbe_select("ddb") != 0)
			printf("The ddb backend could not be selected.\n");
		else {
			printf("using longjmp, hope it works!\n");
			kdb_reenter();
		}
	}
	return (c);
}
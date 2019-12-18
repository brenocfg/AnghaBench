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
struct sa_open_data {int dummy; } ;
typedef  int /*<<< orphan*/  lbuf ;

/* Variables and functions */
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa_open_data_dump (struct sa_open_data*) ; 
 int /*<<< orphan*/  salist_close (struct sa_open_data*) ; 
 int /*<<< orphan*/  salist_cmd_parse (struct sa_open_data*,char*,int /*<<< orphan*/ ) ; 
 struct sa_open_data* salist_open () ; 
 int /*<<< orphan*/  stdin ; 
 size_t strlen (char*) ; 

int main(int argc, char *argv[])
{
	struct sa_open_data *od;
	char lbuf[128];

	od = salist_open();

	while (fgets(lbuf, sizeof(lbuf), stdin)) {
		size_t llen = strlen(lbuf);
		if (llen > 0 && lbuf[llen - 1] == '\n')
			lbuf[--llen] = '\0';
		if (llen > 0 && lbuf[llen - 1] == '\r')
			lbuf[--llen] = '\0';
		if (llen == 0)
			continue;
		salist_cmd_parse(od, lbuf, 0);
	}

	salist_close(od);

	sa_open_data_dump(od);

	return 0;
}
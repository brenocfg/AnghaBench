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
struct TYPE_3__ {int /*<<< orphan*/  (* spring ) () ;int /*<<< orphan*/  arg; } ;

/* Variables and functions */
 unsigned int __arraycount (TYPE_1__*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 TYPE_1__* paragus ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int rumpclient_init () ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 

int
main(int argc, char *argv[])
{
	unsigned i;

	if (argc != 2)
		errx(1, "invalid usage");

	if (rumpclient_init() == -1)
		err(1, "rumpclient init");

	for (i = 0; i < __arraycount(paragus); i++) {
		if (strcmp(argv[1], paragus[i].arg) == 0) {
			paragus[i].spring();
			break;
		}
	}
	if (i == __arraycount(paragus)) {
		printf("invalid test %s\n", argv[1]);
		exit(1);
	}

	exit(0);
}
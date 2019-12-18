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
struct cidr {int dummy; } ;
struct TYPE_4__ {scalar_t__ family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 struct cidr* cidr_parse4 (char*) ; 
 struct cidr* cidr_parse6 (char*) ; 
 int /*<<< orphan*/  cidr_print4 (TYPE_1__*) ; 
 int /*<<< orphan*/  cidr_print6 (TYPE_1__*) ; 
 int /*<<< orphan*/  cidr_push (struct cidr*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  printed ; 
 int /*<<< orphan*/  qprintf (char*) ; 
 scalar_t__ runop (char***,int*) ; 
 TYPE_1__* stack ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char **argv)
{
	int status = 0;
	char **arg = argv+2;
	struct cidr *a;

	if (argc < 3)
		usage(argv[0]);

	a = strchr(argv[1], ':') ? cidr_parse6(argv[1]) : cidr_parse4(argv[1]);

	if (!a)
		usage(argv[0]);

	cidr_push(a);

	while (runop(&arg, &status));

	if (*arg)
	{
		fprintf(stderr, "unknown operation '%s'\n", *arg);
		exit(6);
	}

	if (!printed && (status < 2))
	{
		if (stack->family == AF_INET)
			cidr_print4(stack);
		else
			cidr_print6(stack);
	}

	qprintf("\n");

	exit(status);
}
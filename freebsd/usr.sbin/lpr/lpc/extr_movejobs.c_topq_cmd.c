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

/* Variables and functions */
 int /*<<< orphan*/  IS_TOPQ ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  tqbq_common (int,char**,int /*<<< orphan*/ ) ; 

void
topq_cmd(int argc, char *argv[])
{

	if (argc < 3) {
		printf("usage: topq printer [jobspec ...]\n");
		return;
	}
	--argc;			/* First argv was the command name */
	++argv;

	tqbq_common(argc, argv, IS_TOPQ);
}
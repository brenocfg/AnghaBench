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
typedef  long id_t ;

/* Variables and functions */
 long strtol (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static id_t
parse_id(char *id)
{
	static bool first = true;
	long value;
	char *ch;

	if (!first) {
		warnx("only one -g or -p flag is permitted");
		usage();
	}
	value = strtol(id, &ch, 0);
	if (*ch != '\0') {
		warnx("invalid process id");
		usage();
	}
	return (value);
}
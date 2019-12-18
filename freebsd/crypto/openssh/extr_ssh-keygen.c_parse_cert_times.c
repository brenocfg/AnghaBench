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
typedef  int u_int64_t ;
typedef  int time_t ;
typedef  int int64_t ;

/* Variables and functions */
 int cert_valid_from ; 
 int cert_valid_to ; 
 int convtime (char*) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ parse_absolute_time (char*,int*) ; 
 int parse_relative_time (char*,int) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int time (int /*<<< orphan*/ *) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static void
parse_cert_times(char *timespec)
{
	char *from, *to;
	time_t now = time(NULL);
	int64_t secs;

	/* +timespec relative to now */
	if (*timespec == '+' && strchr(timespec, ':') == NULL) {
		if ((secs = convtime(timespec + 1)) == -1)
			fatal("Invalid relative certificate life %s", timespec);
		cert_valid_to = now + secs;
		/*
		 * Backdate certificate one minute to avoid problems on hosts
		 * with poorly-synchronised clocks.
		 */
		cert_valid_from = ((now - 59)/ 60) * 60;
		return;
	}

	/*
	 * from:to, where
	 * from := [+-]timespec | YYYYMMDD | YYYYMMDDHHMMSS | "always"
	 *   to := [+-]timespec | YYYYMMDD | YYYYMMDDHHMMSS | "forever"
	 */
	from = xstrdup(timespec);
	to = strchr(from, ':');
	if (to == NULL || from == to || *(to + 1) == '\0')
		fatal("Invalid certificate life specification %s", timespec);
	*to++ = '\0';

	if (*from == '-' || *from == '+')
		cert_valid_from = parse_relative_time(from, now);
	else if (strcmp(from, "always") == 0)
		cert_valid_from = 0;
	else if (parse_absolute_time(from, &cert_valid_from) != 0)
		fatal("Invalid from time \"%s\"", from);

	if (*to == '-' || *to == '+')
		cert_valid_to = parse_relative_time(to, now);
	else if (strcmp(to, "forever") == 0)
		cert_valid_to = ~(u_int64_t)0;
	else if (parse_absolute_time(to, &cert_valid_to) != 0)
		fatal("Invalid to time \"%s\"", to);

	if (cert_valid_to <= cert_valid_from)
		fatal("Empty certificate validity interval");
	free(from);
}
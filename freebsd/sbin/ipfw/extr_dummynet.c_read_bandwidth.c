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
 int EX_DATAERR ; 
 int IFNAMSIZ ; 
 scalar_t__ _substrcmp2 (char*,char*,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int strtoul (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
read_bandwidth(char *arg, int *bandwidth, char *if_name, int namelen)
{
	if (*bandwidth != -1)
		warnx("duplicate token, override bandwidth value!");

	if (arg[0] >= 'a' && arg[0] <= 'z') {
		if (!if_name) {
			errx(1, "no if support");
		}
		if (namelen >= IFNAMSIZ)
			warn("interface name truncated");
		namelen--;
		/* interface name */
		strlcpy(if_name, arg, namelen);
		*bandwidth = 0;
	} else {	/* read bandwidth value */
		int bw;
		char *end = NULL;

		bw = strtoul(arg, &end, 0);
		if (*end == 'K' || *end == 'k') {
			end++;
			bw *= 1000;
		} else if (*end == 'M' || *end == 'm') {
			end++;
			bw *= 1000000;
		} else if (*end == 'G' || *end == 'g') {
			end++;
			bw *= 1000000000;
		}
		if ((*end == 'B' &&
			_substrcmp2(end, "Bi", "Bit/s") != 0) ||
		    _substrcmp2(end, "by", "bytes") == 0)
			bw *= 8;

		if (bw < 0)
			errx(EX_DATAERR, "bandwidth too large");

		*bandwidth = bw;
		if (if_name)
			if_name[0] = '\0';
	}
}
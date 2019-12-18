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
 int CHAR_BIT ; 
 int atoi (int /*<<< orphan*/ ) ; 
 scalar_t__ getenv (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 char* prog ; 
 int slot_map ; 
 char* strrchr (char*,char) ; 
 scalar_t__ tmp_dir ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnc (int /*<<< orphan*/ ,char*) ; 

int
proc_arg(int ac, char **av)
{
    int             rc = -1;
    int             ch;

    char           *p = strrchr(av[0], '/');
    prog = p ? p + 1 : av[0];

    tmp_dir = getenv("TMPDIR") ? getenv("TMPDIR") : tmp_dir;

    while ((ch = getopt(ac, av, "ans:")) != -1) {
	switch (ch) {
	case 'a':
	    slot_map = ~0;
	    break;
	case 'n':
	    slot_map = 0;
	    break;
	case 's':
	    {
		int             n = atoi(optarg);
		if (n < 0 || n >= CHAR_BIT * sizeof slot_map) {
		    warnc(0, "Invalid slot number.");
		    usage();
		    goto out;
		}
		if (slot_map == ~0)
		    slot_map = 0;
		slot_map |= 1 << n;
	    }
	    break;
	default:
	    usage();
	    goto out;
	}
    }

    rc = 0;
  out:
    return rc;
}
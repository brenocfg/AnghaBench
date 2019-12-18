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
 char getopt (int,char**,char*) ; 
 int gflag ; 
 int /*<<< orphan*/  list () ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update () ; 
 int /*<<< orphan*/  usage (int) ; 

int
main(int argc, char **argv)
{
	char ch, *s;

	s = NULL;
	while ((ch = getopt(argc, argv, "ghlus:")) != -1) {
		switch (ch) {
		case 'g':
			gflag = 1;
			break;
		case 'h':
			usage(0);
			/* NOTREACHED */
			break;
		case 'l':
			list();
			/* NOTREACHED */
			break;
		case 'u':
			update();
			/* NOTREACHED */
			break;

		case 's':
			set(optarg);
			/* NOTREACHED */
			break;

		case '?':
		default:
			usage(1);
			/* NOTREACHED */
			break;
		}
	}

	usage(1);
	/* NOTREACHED */

	return (0);
}
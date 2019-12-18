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
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  family ; 
 int getopt (int,char**,char*) ; 
 int gflag ; 
 int kflag ; 
 int lflag ; 
 int mflag ; 
 int oflag ; 
 int optind ; 
 int pplan ; 
 int sflag ; 
 int /*<<< orphan*/  usage () ; 

__attribute__((used)) static int
option(int argc, char **argv)
{
	int ch;

	optind = 1;		/* reset getopt */

	while ((ch = getopt(argc, argv, "46gklmpsho")) != -1)
		switch(ch) {
		case '4':
			family = AF_INET;
			break;
		case '6':
			family = AF_INET6;
			break;
		case 'g':
			gflag = 1;
			break;
		case 'k':
			kflag = 1;		/* keep going without utmp */
			break;
		case 'l':
			lflag = 1;		/* long format */
			break;
		case 'm':
			mflag = 1;		/* force exact match of names */
			break;
		case 'p':
			pplan = 1;		/* don't show .plan/.project */
			break;
		case 's':
			sflag = 1;		/* short format */
			break;
		case 'h':
			oflag = 0;		/* remote host info */
			break;
		case 'o':
			oflag = 1;		/* office info */
			break;
		case '?':
		default:
			usage();
		}

	return optind;
}
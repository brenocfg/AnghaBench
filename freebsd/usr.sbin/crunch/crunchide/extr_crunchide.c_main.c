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
 int /*<<< orphan*/  add_file_to_keep_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_to_keep_list (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ hide_syms (char*) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 char* pname ; 
 int /*<<< orphan*/  usage () ; 
 int verbose ; 

int
main(int argc, char **argv)
{
    int ch, errors;

    if(argc > 0) pname = argv[0];

    while ((ch = getopt(argc, argv, "k:f:v")) != -1)
	switch(ch) {
	case 'k':
	    add_to_keep_list(optarg);
	    break;
	case 'f':
	    add_file_to_keep_list(optarg);
	    break;
	case 'v':
	    verbose = 1;
	    break;
	default:
	    usage();
	}

    argc -= optind;
    argv += optind;

    if(argc == 0) usage();

    errors = 0;
    while(argc) {
	if (hide_syms(*argv))
		errors = 1;
	argc--, argv++;
    }

    return errors;
}
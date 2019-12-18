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
 int oseama_entity (int,char**) ; 
 int oseama_extract (int,char**) ; 
 int oseama_info (int,char**) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char **argv) {
	if (argc > 1) {
		if (!strcmp(argv[1], "info"))
			return oseama_info(argc, argv);
		else if (!strcmp(argv[1], "entity"))
			return oseama_entity(argc, argv);
		else if (!strcmp(argv[1], "extract"))
			return oseama_extract(argc, argv);
	}

	usage();
	return 0;
}
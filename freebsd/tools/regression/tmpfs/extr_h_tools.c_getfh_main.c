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
typedef  int /*<<< orphan*/  fhandle_t ;
typedef  int /*<<< orphan*/  fh ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int getfh (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int
getfh_main(int argc, char **argv)
{
	int error;
	fhandle_t fh;

	if (argc < 2)
		return EXIT_FAILURE;

	error = getfh(argv[1], &fh);
	if (error == 0) 
		err(EXIT_FAILURE, "can not getfh");	

	error = write(STDOUT_FILENO, &fh, sizeof(fh));
	if (error == -1) {
		perror("write");
		return EXIT_FAILURE;
	}

	return 0;
}
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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  isc_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_INVALIDFILE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  isc__errno2result (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct stat*,int /*<<< orphan*/ ,int) ; 
 int stat (char const*,struct stat*) ; 

isc_result_t
isc_file_isplainfile(const char *filename) {
	/*
	 * This function returns success if filename is a plain file.
	 */
	struct stat filestat;
	memset(&filestat,0,sizeof(struct stat));

	if ((stat(filename, &filestat)) == -1)
		return(isc__errno2result(errno));

	if(! S_ISREG(filestat.st_mode))
		return(ISC_R_INVALIDFILE);

	return(ISC_R_SUCCESS);
}
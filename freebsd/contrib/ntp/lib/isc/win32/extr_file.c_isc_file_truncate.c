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
typedef  int /*<<< orphan*/  isc_result_t ;
typedef  int /*<<< orphan*/  isc_offset_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int _O_BINARY ; 
 int _O_RDWR ; 
 scalar_t__ _chsize (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  isc__errno2result (int /*<<< orphan*/ ) ; 
 int open (char const*,int) ; 

isc_result_t
isc_file_truncate(const char *filename, isc_offset_t size) {
	int fh;

	REQUIRE(filename != NULL && size >= 0);

	if ((fh = open(filename, _O_RDWR | _O_BINARY)) < 0)
		return (isc__errno2result(errno));

	if(_chsize(fh, size) != 0) {
		close(fh);
		return (isc__errno2result(errno));
	}
	close(fh);

	return (ISC_R_SUCCESS);
}
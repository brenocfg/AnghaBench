#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  absolute; } ;
typedef  TYPE_1__ isc_time_t ;
typedef  int /*<<< orphan*/  isc_result_t ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  GetFileTime (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int _O_BINARY ; 
 int _O_RDONLY ; 
 scalar_t__ _get_osfhandle (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  isc__errno2result (int /*<<< orphan*/ ) ; 
 int open (char const*,int) ; 

isc_result_t
isc_file_getmodtime(const char *file, isc_time_t *time) {
	int fh;

	REQUIRE(file != NULL);
	REQUIRE(time != NULL);

	if ((fh = open(file, _O_RDONLY | _O_BINARY)) < 0)
		return (isc__errno2result(errno));

	if (!GetFileTime((HANDLE) _get_osfhandle(fh),
			 NULL,
			 NULL,
			 &time->absolute))
	{
		close(fh);
		errno = EINVAL;
		return (isc__errno2result(errno));
	}
	close(fh);
	return (ISC_R_SUCCESS);
}
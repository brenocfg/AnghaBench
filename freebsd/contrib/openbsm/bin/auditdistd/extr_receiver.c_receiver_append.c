#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_2__ {int adh_trail_fd; int /*<<< orphan*/  adh_trail_name; int /*<<< orphan*/  adh_directory; } ;

/* Variables and functions */
 int ADIST_ERROR_WRITE ; 
 int ADIST_ERROR_WRONG_ORDER ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 TYPE_1__* adhost ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  pjdlog_debug (int,char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pjdlog_errno (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pjdlog_error (char*) ; 
 int write (int,unsigned char const*,size_t) ; 

__attribute__((used)) static int
receiver_append(const unsigned char *data, size_t size)
{
	ssize_t done;
	size_t osize;

	/* We should have opened trail file. */
	if (adhost->adh_trail_fd == -1) {
		pjdlog_error("Sender requested append without first opening file.");
		return (ADIST_ERROR_WRONG_ORDER);
	}

	osize = size;
	while (size > 0) {
		done = write(adhost->adh_trail_fd, data, size);
		if (done == -1) {
			if (errno == EINTR)
				continue;
			pjdlog_errno(LOG_ERR, "Write to \"%s/%s\" failed",
			    adhost->adh_directory, adhost->adh_trail_name);
			PJDLOG_ASSERT(errno > 0);
			return (ADIST_ERROR_WRITE);
		}
		pjdlog_debug(3, "Wrote %zd bytes into \"%s/%s\".", done,
		    adhost->adh_directory, adhost->adh_trail_name);
		size -= done;
	}
	pjdlog_debug(2, "Appended %zu bytes to file \"%s/%s\".",
	    osize, adhost->adh_directory, adhost->adh_trail_name);
	return (0);
}
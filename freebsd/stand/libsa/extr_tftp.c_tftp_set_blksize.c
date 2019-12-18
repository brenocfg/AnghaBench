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
struct tftp_handle {int tftp_blksize; } ;

/* Variables and functions */
 int TFTP_MAX_BLKSIZE ; 
 scalar_t__ strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tftp_set_blksize(struct tftp_handle *h, const char *str)
{
	char *endptr;
	int new_blksize;
	int ret = 0;

	if (h == NULL || str == NULL)
		return (ret);

	new_blksize =
	    (unsigned int)strtol(str, &endptr, 0);

	/*
	 * Only accept blksize value if it is numeric.
	 * RFC2348 specifies that acceptable values are 8-65464.
	 * Let's choose a limit less than MAXRSPACE.
	 */
	if (*endptr == '\0' && new_blksize >= 8 &&
	    new_blksize <= TFTP_MAX_BLKSIZE) {
		h->tftp_blksize = new_blksize;
		ret = 1;
	}

	return (ret);
}
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
 int SIZE (char const* const*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,char const* const,int) ; 

char const *
hci_hmode2str(int mode, char *buffer, int size)
{
	static char const * const	t[] = {
		/* 0x01 */ "Suspend Page Scan ",
		/* 0x02 */ "Suspend Inquiry Scan ",
		/* 0x04 */ "Suspend Periodic Inquiries "
        };

	if (buffer != NULL && size > 0) {
		int	n;

		memset(buffer, 0, size);
		for (n = 0; n < SIZE(t); n++) {
			int	len = strlen(buffer);

			if (len >= size)
				break;
			if (mode & (1 << n))
				strncat(buffer, t[n], size - len);
		}
	}

	return (buffer);
}
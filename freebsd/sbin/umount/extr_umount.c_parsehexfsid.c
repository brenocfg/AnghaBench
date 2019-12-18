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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  fsid_t ;

/* Variables and functions */
 int /*<<< orphan*/  isxdigit (char) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strtol (char*,int /*<<< orphan*/ *,int) ; 

int
parsehexfsid(const char *hex, fsid_t *fsid)
{
	char hexbuf[3];
	int i;

	if (strlen(hex) != sizeof(*fsid) * 2)
		return (-1);
	hexbuf[2] = '\0';
	for (i = 0; i < (int)sizeof(*fsid); i++) {
		hexbuf[0] = hex[i * 2];
		hexbuf[1] = hex[i * 2 + 1];
		if (!isxdigit(hexbuf[0]) || !isxdigit(hexbuf[1]))
			return (-1);
		((u_char *)fsid)[i] = strtol(hexbuf, NULL, 16);
	}
	return (0);
}
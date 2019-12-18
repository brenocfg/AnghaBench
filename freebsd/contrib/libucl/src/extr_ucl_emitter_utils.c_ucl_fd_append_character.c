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
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* malloc (size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,unsigned char,size_t) ; 
 int write (int,unsigned char*,size_t) ; 

__attribute__((used)) static int
ucl_fd_append_character (unsigned char c, size_t len, void *ud)
{
	int fd = *(int *)ud;
	unsigned char *buf;

	if (len == 1) {
		return write (fd, &c, 1);
	}
	else {
		buf = malloc (len);
		if (buf == NULL) {
			/* Fallback */
			while (len --) {
				if (write (fd, &c, 1) == -1) {
					return -1;
				}
			}
		}
		else {
			memset (buf, c, len);
			if (write (fd, buf, len) == -1) {
				free(buf);
				return -1;
			}
			free (buf);
		}
	}

	return 0;
}
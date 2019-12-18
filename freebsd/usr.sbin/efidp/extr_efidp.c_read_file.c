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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ ssize_t ;
typedef  int off_t ;

/* Variables and functions */
 size_t MAXSIZE ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 scalar_t__ read (int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ssize_t
read_file(int fd, void **rv) 
{
	uint8_t *retval;
	size_t len;
	off_t off;
	ssize_t red;

	len = MAXSIZE;
	off = 0;
	retval = malloc(len);
	do {
		red = read(fd, retval + off, len - off);
		if (red == 0)
			break;
		off += red;
		if (off == (off_t)len)
			break;
	} while (1);
	*rv = retval;

	return off;
}
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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  len ;

/* Variables and functions */
 void* calloc (int,size_t) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int read (int,void*,size_t) ; 

void
receive_chunk(void **bufp, size_t *lenp, int pipefd)
{
	ssize_t ret;
	size_t len;
	void *buf;

	ret = read(pipefd, &len, sizeof(len));
	if (ret != sizeof(len))
		err(1, "read");

	buf = calloc(1, len);
	if (buf == NULL)
		err(1, "calloc");

	ret = read(pipefd, buf, len);
	if (ret != (ssize_t)len)
		err(1, "read");

	*bufp = buf;
	*lenp = len;
}
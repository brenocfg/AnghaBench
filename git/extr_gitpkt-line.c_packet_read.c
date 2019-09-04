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
 int /*<<< orphan*/  packet_read_with_status (int,char**,size_t*,char*,unsigned int,int*,int) ; 

int packet_read(int fd, char **src_buffer, size_t *src_len,
		char *buffer, unsigned size, int options)
{
	int pktlen = -1;

	packet_read_with_status(fd, src_buffer, src_len, buffer, size,
				&pktlen, options);

	return pktlen;
}
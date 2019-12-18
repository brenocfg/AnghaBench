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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ FETCH_READ_ERROR ; 
 scalar_t__ FETCH_READ_WAIT ; 
 scalar_t__ errno ; 
 scalar_t__ fetchRestartCalls ; 
 scalar_t__ read (int,char*,size_t) ; 

__attribute__((used)) static ssize_t
fetch_socket_read(int sd, char *buf, size_t len)
{
	ssize_t rlen;

	rlen = read(sd, buf, len);
	if (rlen < 0) {
		if (errno == EAGAIN || (errno == EINTR && fetchRestartCalls))
			return (FETCH_READ_WAIT);
		else
			return (FETCH_READ_ERROR);
	}
	return (rlen);
}
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
 scalar_t__ read_request_eof (int,unsigned char**) ; 
 scalar_t__ read_request_fixed_len (int,scalar_t__,unsigned char**) ; 

__attribute__((used)) static ssize_t read_request(int fd, unsigned char **out, ssize_t req_len)
{
	if (req_len < 0)
		return read_request_eof(fd, out);
	else
		return read_request_fixed_len(fd, req_len, out);
}
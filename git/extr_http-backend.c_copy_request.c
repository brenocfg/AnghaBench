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
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  die_errno (char*) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ read_request (int /*<<< orphan*/ ,unsigned char**,scalar_t__) ; 
 int /*<<< orphan*/  write_to_child (int,unsigned char*,scalar_t__,char const*) ; 

__attribute__((used)) static void copy_request(const char *prog_name, int out, ssize_t req_len)
{
	unsigned char *buf;
	ssize_t n = read_request(0, &buf, req_len);
	if (n < 0)
		die_errno("error reading request body");
	write_to_child(out, buf, n, prog_name);
	close(out);
	free(buf);
}
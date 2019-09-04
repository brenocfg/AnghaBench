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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  die_errno (char*) ; 
 int /*<<< orphan*/  write_to_child (int,unsigned char*,scalar_t__,char const*) ; 
 scalar_t__ xread (int /*<<< orphan*/ ,unsigned char*,size_t) ; 

__attribute__((used)) static void pipe_fixed_length(const char *prog_name, int out, size_t req_len)
{
	unsigned char buf[8192];
	size_t remaining_len = req_len;

	while (remaining_len > 0) {
		size_t chunk_length = remaining_len > sizeof(buf) ? sizeof(buf) : remaining_len;
		ssize_t n = xread(0, buf, chunk_length);
		if (n < 0)
			die_errno("Reading request failed");
		write_to_child(out, buf, n, prog_name);
		remaining_len -= n;
	}

	close(out);
}
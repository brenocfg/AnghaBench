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
 size_t rrecv (int,char*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t _recv(int rs, char *msg, size_t len)
{
	size_t ret, offset;

	for (offset = 0; offset < len; offset += ret) {
		ret = rrecv(rs, msg + offset, len - offset, 0);
		if (ret <= 0)
			return ret;
	}

	return len;
}
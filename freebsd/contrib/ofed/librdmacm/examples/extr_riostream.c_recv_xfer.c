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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  buf ; 
 scalar_t__* poll_byte ; 
 scalar_t__ verify ; 
 int verify_buf (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int recv_xfer(int size, uint8_t marker)
{
	int ret;

	while (*poll_byte != marker)
		;

	if (verify) {
		ret = verify_buf(buf, size - 1);
		if (ret)
			return ret;
	}

	return 0;
}
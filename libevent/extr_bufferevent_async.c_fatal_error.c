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
#define  ERROR_INVALID_PARAMETER 128 

__attribute__((used)) static inline int
fatal_error(int err)
{
	switch (err) {
		/* We may have already associated this fd with a port.
		 * Let's hope it's this port, and that the error code
		 * for doing this neer changes. */
		case ERROR_INVALID_PARAMETER:
			return 0;
	}
	return 1;
}
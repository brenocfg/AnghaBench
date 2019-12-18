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
#define  LINUX_SOL_SOCKET 128 
 int SOL_SOCKET ; 

__attribute__((used)) static int
linux_to_bsd_sockopt_level(int level)
{

	switch (level) {
	case LINUX_SOL_SOCKET:
		return (SOL_SOCKET);
	}
	return (level);
}
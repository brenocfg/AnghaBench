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
#define  ADIST_ROLE_RECEIVER 129 
#define  ADIST_ROLE_SENDER 128 

const char *
role2str(int role)
{

	switch (role) {
	case ADIST_ROLE_SENDER:
		return ("sender");
	case ADIST_ROLE_RECEIVER:
		return ("receiver");
	}
	return ("unknown");
}
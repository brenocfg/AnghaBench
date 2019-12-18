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
#define  HAST_ROLE_INIT 130 
#define  HAST_ROLE_PRIMARY 129 
#define  HAST_ROLE_SECONDARY 128 

const char *
role2str(int role)
{

	switch (role) {
	case HAST_ROLE_INIT:
		return ("init");
	case HAST_ROLE_PRIMARY:
		return ("primary");
	case HAST_ROLE_SECONDARY:
		return ("secondary");
	}
	return ("unknown");
}
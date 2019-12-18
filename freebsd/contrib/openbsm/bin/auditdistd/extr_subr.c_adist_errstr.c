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
#define  ADIST_ERROR_CREATE 135 
#define  ADIST_ERROR_INVALID_NAME 134 
#define  ADIST_ERROR_OPEN 133 
#define  ADIST_ERROR_OPEN_OLD 132 
#define  ADIST_ERROR_READ 131 
#define  ADIST_ERROR_RENAME 130 
#define  ADIST_ERROR_WRITE 129 
#define  ADIST_ERROR_WRONG_ORDER 128 

const char *
adist_errstr(int error)
{

	switch (error) {
	case ADIST_ERROR_WRONG_ORDER:
		return ("wrong operations order");
	case ADIST_ERROR_INVALID_NAME:
		return ("invalid trail file name");
	case ADIST_ERROR_OPEN_OLD:
		return ("attempt to open an old trail file");
	case ADIST_ERROR_CREATE:
		return ("creation of new trail file failed");
	case ADIST_ERROR_OPEN:
		return ("open of existing trail file failed");
	case ADIST_ERROR_READ:
		return ("read failed");
	case ADIST_ERROR_WRITE:
		return ("write failed");
	case ADIST_ERROR_RENAME:
		return ("rename of a trail file failed");
	default:
		return ("unknown error");
	}
}
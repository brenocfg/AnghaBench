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
#define  MEMSTAT_ERROR_DATAERROR 135 
#define  MEMSTAT_ERROR_KVM 134 
#define  MEMSTAT_ERROR_KVM_NOSYMBOL 133 
#define  MEMSTAT_ERROR_KVM_SHORTREAD 132 
#define  MEMSTAT_ERROR_NOMEMORY 131 
#define  MEMSTAT_ERROR_PERMISSION 130 
#define  MEMSTAT_ERROR_UNDEFINED 129 
#define  MEMSTAT_ERROR_VERSION 128 

const char *
memstat_strerror(int error)
{

	switch (error) {
	case MEMSTAT_ERROR_NOMEMORY:
		return ("Cannot allocate memory");
	case MEMSTAT_ERROR_VERSION:
		return ("Version mismatch");
	case MEMSTAT_ERROR_PERMISSION:
		return ("Permission denied");
	case MEMSTAT_ERROR_DATAERROR:
		return ("Data format error");
	case MEMSTAT_ERROR_KVM:
		return ("KVM error");
	case MEMSTAT_ERROR_KVM_NOSYMBOL:
		return ("KVM unable to find symbol");
	case MEMSTAT_ERROR_KVM_SHORTREAD:
		return ("KVM short read");
	case MEMSTAT_ERROR_UNDEFINED:
	default:
		return ("Unknown error");
	}
}
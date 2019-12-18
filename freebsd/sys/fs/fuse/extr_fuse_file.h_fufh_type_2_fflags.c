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
typedef  int fufh_type_t ;

/* Variables and functions */
#define  FUFH_EXEC 131 
#define  FUFH_RDONLY 130 
#define  FUFH_RDWR 129 
#define  FUFH_WRONLY 128 

__attribute__((used)) static inline int
fufh_type_2_fflags(fufh_type_t type)
{
	int oflags = -1;

	switch (type) {
	case FUFH_RDONLY:
	case FUFH_WRONLY:
	case FUFH_RDWR:
	case FUFH_EXEC:
		oflags = type;
		break;
	default:
		break;
	}

	return oflags;
}
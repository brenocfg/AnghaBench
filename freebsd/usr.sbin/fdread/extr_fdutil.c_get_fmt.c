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
struct fd_type {int size; int sectrac; int heads; int tracks; int secsize; } ;
typedef  enum fd_drivetype { ____Placeholder_fd_drivetype } fd_drivetype ;

/* Variables and functions */
#define  FDT_12M 132 
#define  FDT_144M 131 
#define  FDT_288M 130 
#define  FDT_360K 129 
#define  FDT_720K 128 
 struct fd_type* fd_types_12m ; 
 struct fd_type* fd_types_144m ; 
 struct fd_type* fd_types_288m ; 
 struct fd_type* fd_types_360k ; 
 struct fd_type* fd_types_720k ; 
 struct fd_type* fd_types_auto ; 

struct fd_type *
get_fmt(int size, enum fd_drivetype type)
{
	int i, n;
	struct fd_type *fdtp;

	switch (type) {
	default:
		return (0);

	case FDT_360K:
		fdtp = fd_types_360k;
		n = sizeof fd_types_360k / sizeof(struct fd_type);
		break;

	case FDT_720K:
		fdtp = fd_types_720k;
		n = sizeof fd_types_720k / sizeof(struct fd_type);
		break;

	case FDT_12M:
		fdtp = fd_types_12m;
		n = sizeof fd_types_12m / sizeof(struct fd_type);
		break;

	case FDT_144M:
		fdtp = fd_types_144m;
		n = sizeof fd_types_144m / sizeof(struct fd_type);
		break;

	case FDT_288M:
		fdtp = fd_types_288m;
		n = sizeof fd_types_288m / sizeof(struct fd_type);
		break;
	}

	if (size == -1)
		return fd_types_auto;

	for (i = 0; i < n; i++, fdtp++) {
		fdtp->size = fdtp->sectrac * fdtp->heads * fdtp->tracks;
		if (((128 << fdtp->secsize) * fdtp->size / 1024) == size)
			return (fdtp);
	}
	return (0);
}
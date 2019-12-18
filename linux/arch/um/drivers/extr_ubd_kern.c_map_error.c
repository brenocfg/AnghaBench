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
 int BLK_STS_IOERR ; 
 int BLK_STS_NOSPC ; 
 int BLK_STS_NOTSUPP ; 
 int BLK_STS_OK ; 
#define  ENOSPC 130 
#define  ENOSYS 129 
#define  EOPNOTSUPP 128 

__attribute__((used)) static int map_error(int error_code)
{
	switch (error_code) {
	case 0:
		return BLK_STS_OK;
	case ENOSYS:
	case EOPNOTSUPP:
		return BLK_STS_NOTSUPP;
	case ENOSPC:
		return BLK_STS_NOSPC;
	}
	return BLK_STS_IOERR;
}
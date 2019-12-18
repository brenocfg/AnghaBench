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
typedef  int rd_err_e ;

/* Variables and functions */
#define  RD_DBERR 133 
#define  RD_ERR 132 
#define  RD_NOBASE 131 
#define  RD_NOCAPAB 130 
#define  RD_NOMAPS 129 
#define  RD_OK 128 

const char *
rd_errstr(rd_err_e rderr)
{

	switch (rderr) {
	case RD_ERR:
		return "generic error";
	case RD_OK:
		return "no error";
	case RD_NOCAPAB:
		return "capability not supported";
	case RD_DBERR:
		return "database error";
	case RD_NOBASE:
		return "NOBASE";
	case RD_NOMAPS:
		return "NOMAPS";
	default:
		return "unknown error";
	}
}
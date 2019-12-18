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
#define  ERR_ACCESS 133 
#define  ERR_DBASE 132 
#define  ERR_KEY 131 
#define  ERR_MALLOC 130 
#define  ERR_READ 129 
#define  ERR_WRITE 128 

__attribute__((used)) static const char *
err_string(int code)
{
	const char *pmesg;

	switch (code) {
	case 0:
		pmesg = "update operation succeeded";
		break;
	case ERR_KEY:
		pmesg = "no such key in file";
		break;
	case ERR_READ:
		pmesg = "cannot read the database";
		break;
	case ERR_WRITE:
		pmesg = "cannot write to the database";
		break;
	case ERR_DBASE:
		pmesg = "cannot update database";
		break;
	case ERR_ACCESS:
		pmesg = "permission denied";
		break;
	case ERR_MALLOC:
		pmesg = "malloc failed";
		break;
	default:
		pmesg = "unknown error";
		break;
	}
	return (pmesg);
}
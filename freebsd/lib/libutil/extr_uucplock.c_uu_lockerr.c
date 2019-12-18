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
typedef  int /*<<< orphan*/  errbuf ;

/* Variables and functions */
#define  UU_LOCK_CREAT_ERR 136 
#define  UU_LOCK_INUSE 135 
#define  UU_LOCK_LINK_ERR 134 
#define  UU_LOCK_OK 133 
#define  UU_LOCK_OPEN_ERR 132 
#define  UU_LOCK_OWNER_ERR 131 
#define  UU_LOCK_READ_ERR 130 
#define  UU_LOCK_TRY_ERR 129 
#define  UU_LOCK_WRITE_ERR 128 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  snprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

const char *
uu_lockerr(int uu_lockresult)
{
	static char errbuf[128];
	const char *fmt;

	switch (uu_lockresult) {
		case UU_LOCK_INUSE:
			return "device in use";
		case UU_LOCK_OK:
			return "";
		case UU_LOCK_OPEN_ERR:
			fmt = "open error: %s";
			break;
		case UU_LOCK_READ_ERR:
			fmt = "read error: %s";
			break;
		case UU_LOCK_CREAT_ERR:
			fmt = "creat error: %s";
			break;
		case UU_LOCK_WRITE_ERR:
			fmt = "write error: %s";
			break;
		case UU_LOCK_LINK_ERR:
			fmt = "link error: %s";
			break;
		case UU_LOCK_TRY_ERR:
			fmt = "too many tries: %s";
			break;
		case UU_LOCK_OWNER_ERR:
			fmt = "not locking process: %s";
			break;
		default:
			fmt = "undefined error: %s";
			break;
	}

	(void)snprintf(errbuf, sizeof(errbuf), fmt, strerror(errno));
	return errbuf;
}
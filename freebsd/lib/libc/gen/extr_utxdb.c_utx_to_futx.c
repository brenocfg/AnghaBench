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
struct utmpx {int ut_type; } ;
struct futx {int /*<<< orphan*/  fu_type; } ;

/* Variables and functions */
#define  BOOT_TIME 135 
#define  DEAD_PROCESS 134 
 int /*<<< orphan*/  EMPTY ; 
#define  INIT_PROCESS 133 
#define  LOGIN_PROCESS 132 
#define  NEW_TIME 131 
#define  OLD_TIME 130 
#define  SHUTDOWN_TIME 129 
#define  USER_PROCESS 128 
 int /*<<< orphan*/  UTOF_ID (struct utmpx const*,struct futx*) ; 
 int /*<<< orphan*/  UTOF_PID (struct utmpx const*,struct futx*) ; 
 int /*<<< orphan*/  UTOF_STRING (struct utmpx const*,struct futx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UTOF_TV (struct futx*) ; 
 int /*<<< orphan*/  UTOF_TYPE (struct utmpx const*,struct futx*) ; 
 int /*<<< orphan*/  host ; 
 int /*<<< orphan*/  line ; 
 int /*<<< orphan*/  memset (struct futx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  user ; 

void
utx_to_futx(const struct utmpx *ut, struct futx *fu)
{

	memset(fu, 0, sizeof *fu);

	switch (ut->ut_type) {
	case BOOT_TIME:
	case OLD_TIME:
	case NEW_TIME:
	/* Extension: shutdown time. */
	case SHUTDOWN_TIME:
		break;
	case USER_PROCESS:
		UTOF_ID(ut, fu);
		UTOF_STRING(ut, fu, user);
		UTOF_STRING(ut, fu, line);
		/* Extension: host name. */
		UTOF_STRING(ut, fu, host);
		UTOF_PID(ut, fu);
		break;
	case INIT_PROCESS:
		UTOF_ID(ut, fu);
		UTOF_PID(ut, fu);
		break;
	case LOGIN_PROCESS:
		UTOF_ID(ut, fu);
		UTOF_STRING(ut, fu, user);
		UTOF_STRING(ut, fu, line);
		UTOF_PID(ut, fu);
		break;
	case DEAD_PROCESS:
		UTOF_ID(ut, fu);
		UTOF_PID(ut, fu);
		break;
	default:
		fu->fu_type = EMPTY;
		return;
	}

	UTOF_TYPE(ut, fu);
	UTOF_TV(fu);
}
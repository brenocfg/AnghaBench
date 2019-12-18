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
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 

__attribute__((used)) static const char *
login_target_error_str(int class, int detail)
{
	static char msg[128];

	/*
	 * RFC 3270, 10.13.5.  Status-Class and Status-Detail
	 */
	switch (class) {
	case 0x01:
		switch (detail) {
		case 0x01:
			return ("Target moved temporarily");
		case 0x02:
			return ("Target moved permanently");
		default:
			snprintf(msg, sizeof(msg), "unknown redirection; "
			    "Status-Class 0x%x, Status-Detail 0x%x",
			    class, detail);
			return (msg);
		}
	case 0x02:
		switch (detail) {
		case 0x00:
			return ("Initiator error");
		case 0x01:
			return ("Authentication failure");
		case 0x02:
			return ("Authorization failure");
		case 0x03:
			return ("Not found");
		case 0x04:
			return ("Target removed");
		case 0x05:
			return ("Unsupported version");
		case 0x06:
			return ("Too many connections");
		case 0x07:
			return ("Missing parameter");
		case 0x08:
			return ("Can't include in session");
		case 0x09:
			return ("Session type not supported");
		case 0x0a:
			return ("Session does not exist");
		case 0x0b:
			return ("Invalid during login");
		default:
			snprintf(msg, sizeof(msg), "unknown initiator error; "
			    "Status-Class 0x%x, Status-Detail 0x%x",
			    class, detail);
			return (msg);
		}
	case 0x03:
		switch (detail) {
		case 0x00:
			return ("Target error");
		case 0x01:
			return ("Service unavailable");
		case 0x02:
			return ("Out of resources");
		default:
			snprintf(msg, sizeof(msg), "unknown target error; "
			    "Status-Class 0x%x, Status-Detail 0x%x",
			    class, detail);
			return (msg);
		}
	default:
		snprintf(msg, sizeof(msg), "unknown error; "
		    "Status-Class 0x%x, Status-Detail 0x%x",
		    class, detail);
		return (msg);
	}
}
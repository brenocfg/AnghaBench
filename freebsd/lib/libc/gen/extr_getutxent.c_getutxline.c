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
struct utmpx {int /*<<< orphan*/  ut_line; } ;
struct futx {int fu_type; int /*<<< orphan*/  fu_line; } ;

/* Variables and functions */
#define  LOGIN_PROCESS 129 
 int /*<<< orphan*/  MIN (int,int) ; 
#define  USER_PROCESS 128 
 struct utmpx* futx_to_utx (struct futx*) ; 
 scalar_t__ getfutxent (struct futx*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct utmpx *
getutxline(const struct utmpx *line)
{
	struct futx fu;

	for (;;) {
		if (getfutxent(&fu) != 0)
			return (NULL);

		switch (fu.fu_type) {
		case USER_PROCESS:
		case LOGIN_PROCESS:
			if (strncmp(fu.fu_line, line->ut_line,
			    MIN(sizeof(fu.fu_line), sizeof(line->ut_line))) ==
			    0)
				goto found;
			break;
		}
	}

found:
	return (futx_to_utx(&fu));
}
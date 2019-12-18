#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int max; } ;
struct TYPE_5__ {TYPE_1__ qc; } ;
typedef  TYPE_2__ params_t ;
typedef  int /*<<< orphan*/  pam_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  MESSAGE_TOOLONG ; 
 int /*<<< orphan*/  MESSAGE_TRUNCATED ; 
 int /*<<< orphan*/  PAM_ERROR_MSG ; 
 int /*<<< orphan*/  PAM_TEXT_INFO ; 
 int /*<<< orphan*/  say (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int check_max(params_t *params, pam_handle_t *pamh, const char *newpass)
{
	if ((int)strlen(newpass) > params->qc.max) {
		if (params->qc.max != 8) {
			say(pamh, PAM_ERROR_MSG, MESSAGE_TOOLONG);
			return -1;
		}
		say(pamh, PAM_TEXT_INFO, MESSAGE_TRUNCATED);
	}

	return 0;
}
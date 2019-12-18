#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ ** env; } ;
typedef  TYPE_1__ pam_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENTERS (char const*) ; 
 int /*<<< orphan*/  RETURNS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int openpam_findenv (TYPE_1__*,char const*,size_t) ; 

const char *
pam_getenv(pam_handle_t *pamh,
	const char *name)
{
	size_t len;
	int i;

	ENTERS(name);
	for (len = 0; name[len] != '\0'; ++len) {
		if (name[len] == '=') {
			errno = EINVAL;
			RETURNS(NULL);
		}
	}
	if ((i = openpam_findenv(pamh, name, len)) < 0)
		RETURNS(NULL);
	/* assert(pamh->env[i][len] == '='); */
	RETURNS(pamh->env[i] + len + 1);
}
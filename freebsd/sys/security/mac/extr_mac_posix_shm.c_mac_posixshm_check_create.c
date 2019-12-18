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
struct ucred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK_PROBE2 (int /*<<< orphan*/ ,int,struct ucred*,char const*) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK_NOSLEEP (int /*<<< orphan*/ ,struct ucred*,char const*) ; 
 int /*<<< orphan*/  posixshm_check_create ; 

int
mac_posixshm_check_create(struct ucred *cred, const char *path)
{
	int error;

	MAC_POLICY_CHECK_NOSLEEP(posixshm_check_create, cred, path);
	MAC_CHECK_PROBE2(posixshm_check_create, error, cred, path);

	return (error);
}
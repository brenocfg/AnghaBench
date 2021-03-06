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
struct ucred {int /*<<< orphan*/  cr_label; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTER_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LABEL_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_CRED ; 
 int /*<<< orphan*/  cred_check_setresgid ; 

__attribute__((used)) static int
test_cred_check_setresgid(struct ucred *cred, gid_t rgid, gid_t egid,
	gid_t sgid)
{

	LABEL_CHECK(cred->cr_label, MAGIC_CRED);
	COUNTER_INC(cred_check_setresgid);

	return (0);
}
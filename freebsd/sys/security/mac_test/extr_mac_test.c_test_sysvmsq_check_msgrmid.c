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
struct ucred {struct label* cr_label; } ;
struct msg {int dummy; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTER_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LABEL_CHECK (struct label*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_CRED ; 
 int /*<<< orphan*/  MAGIC_SYSV_MSG ; 
 int /*<<< orphan*/  sysvmsq_check_msgrmid ; 

__attribute__((used)) static int
test_sysvmsq_check_msgrmid(struct ucred *cred, struct msg *msgptr,
    struct label *msglabel)
{

	LABEL_CHECK(msglabel, MAGIC_SYSV_MSG);
	LABEL_CHECK(cred->cr_label, MAGIC_CRED);
	COUNTER_INC(sysvmsq_check_msgrmid);

	return (0);
}
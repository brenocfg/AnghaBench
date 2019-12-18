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
struct msqid_kernel {int dummy; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTER_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LABEL_CHECK (struct label*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_CRED ; 
 int /*<<< orphan*/  MAGIC_SYSV_MSQ ; 
 int /*<<< orphan*/  sysvmsq_check_msqsnd ; 

__attribute__((used)) static int
test_sysvmsq_check_msqsnd(struct ucred *cred,
    struct msqid_kernel *msqkptr, struct label *msqklabel)
{

	LABEL_CHECK(msqklabel, MAGIC_SYSV_MSQ);
	LABEL_CHECK(cred->cr_label, MAGIC_CRED);
	COUNTER_INC(sysvmsq_check_msqsnd);

	return (0);
}
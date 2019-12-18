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
typedef  int /*<<< orphan*/  uid_t ;
struct ucred {struct label* cr_label; } ;
struct label {int dummy; } ;
struct ksem {int dummy; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTER_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LABEL_CHECK (struct label*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_CRED ; 
 int /*<<< orphan*/  MAGIC_POSIX_SHM ; 
 int /*<<< orphan*/  posixsem_check_setowner ; 

__attribute__((used)) static int
test_posixsem_check_setowner(struct ucred *cred, struct ksem *ks,
    struct label *kslabel, uid_t uid, gid_t gid)
{

	LABEL_CHECK(cred->cr_label, MAGIC_CRED);
	LABEL_CHECK(kslabel, MAGIC_POSIX_SHM);
	COUNTER_INC(posixsem_check_setowner);
	return (0);
}
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
struct shmfd {int dummy; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTER_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LABEL_CHECK (struct label*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_CRED ; 
 int /*<<< orphan*/  MAGIC_POSIX_SHM ; 
 int /*<<< orphan*/  posixshm_check_mmap ; 

__attribute__((used)) static int
test_posixshm_check_mmap(struct ucred *cred, struct shmfd *shmfd,
    struct label *shmfdlabel, int prot, int flags)
{

	LABEL_CHECK(cred->cr_label, MAGIC_CRED);
	LABEL_CHECK(shmfdlabel, MAGIC_POSIX_SHM);
	COUNTER_INC(posixshm_check_mmap);
	return (0);
}
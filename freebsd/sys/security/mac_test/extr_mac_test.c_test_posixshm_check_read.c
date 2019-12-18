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
 int /*<<< orphan*/  posixshm_check_read ; 

__attribute__((used)) static int
test_posixshm_check_read(struct ucred *active_cred,
    struct ucred *file_cred, struct shmfd *shm, struct label *shmlabel)
{

	LABEL_CHECK(active_cred->cr_label, MAGIC_CRED);
	if (file_cred != NULL)
		LABEL_CHECK(file_cred->cr_label, MAGIC_CRED);
	LABEL_CHECK(shmlabel, MAGIC_POSIX_SHM);
	COUNTER_INC(posixshm_check_read);

	return (0);
}
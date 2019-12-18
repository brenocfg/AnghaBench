#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t n_len; char* n_bytes; } ;
struct TYPE_4__ {size_t n_len; void* n_bytes; } ;
struct nlm4_lock {int svid; scalar_t__ l_len; scalar_t__ l_offset; TYPE_2__ oh; TYPE_1__ fh; int /*<<< orphan*/  caller_name; } ;
struct flock {scalar_t__ l_whence; scalar_t__ l_start; scalar_t__ l_len; } ;
typedef  scalar_t__ rpcvers_t ;
typedef  scalar_t__ off_t ;
struct TYPE_6__ {int /*<<< orphan*/  pr_hostname; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOVERFLOW ; 
 scalar_t__ NLM_VERS ; 
 scalar_t__ OFF_MAX ; 
 scalar_t__ SEEK_CUR ; 
 scalar_t__ SEEK_END ; 
 scalar_t__ SEEK_SET ; 
 int /*<<< orphan*/  getcredhostname (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memset (struct nlm4_lock*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__ prison0 ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int
nlm_init_lock(struct flock *fl, int flags, int svid,
    rpcvers_t vers, size_t fhlen, void *fh, off_t size,
    struct nlm4_lock *lock, char oh_space[32])
{
	size_t oh_len;
	off_t start, len;

	if (fl->l_whence == SEEK_END) {
		if (size > OFF_MAX
		    || (fl->l_start > 0 && size > OFF_MAX - fl->l_start))
			return (EOVERFLOW);
		start = size + fl->l_start;
	} else if (fl->l_whence == SEEK_SET || fl->l_whence == SEEK_CUR) {
		start = fl->l_start;
	} else {
		return (EINVAL);
	}
	if (start < 0)
		return (EINVAL);
	if (fl->l_len < 0) {
		len = -fl->l_len;
		start -= len;
		if (start < 0)
			return (EINVAL);
	} else {
		len = fl->l_len;
	}

	if (vers == NLM_VERS) {
		/*
		 * Enforce range limits on V1 locks
		 */
		if (start > 0xffffffffLL || len > 0xffffffffLL)
			return (EOVERFLOW);
	}

	snprintf(oh_space, 32, "%d@", svid);
	oh_len = strlen(oh_space);
	getcredhostname(NULL, oh_space + oh_len, 32 - oh_len);
	oh_len = strlen(oh_space);

	memset(lock, 0, sizeof(*lock));
	lock->caller_name = prison0.pr_hostname;
	lock->fh.n_len = fhlen;
	lock->fh.n_bytes = fh;
	lock->oh.n_len = oh_len;
	lock->oh.n_bytes = oh_space;
	lock->svid = svid;
	lock->l_offset = start;
	lock->l_len = len;

	return (0);
}
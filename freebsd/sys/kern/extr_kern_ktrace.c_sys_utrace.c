#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct utrace_args {int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct thread {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ktr_len; } ;
struct ktr_request {TYPE_1__ ktr_header; void* ktr_buffer; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  KTRPOINT (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_USER ; 
 int /*<<< orphan*/  KTR_USER_MAXLEN ; 
 int /*<<< orphan*/  M_KTRACE ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int copyin (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 struct ktr_request* ktr_getrequest (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktr_submitrequest (struct thread*,struct ktr_request*) ; 
 void* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_utrace(struct thread *td, struct utrace_args *uap)
{

#ifdef KTRACE
	struct ktr_request *req;
	void *cp;
	int error;

	if (!KTRPOINT(td, KTR_USER))
		return (0);
	if (uap->len > KTR_USER_MAXLEN)
		return (EINVAL);
	cp = malloc(uap->len, M_KTRACE, M_WAITOK);
	error = copyin(uap->addr, cp, uap->len);
	if (error) {
		free(cp, M_KTRACE);
		return (error);
	}
	req = ktr_getrequest(KTR_USER);
	if (req == NULL) {
		free(cp, M_KTRACE);
		return (ENOMEM);
	}
	req->ktr_buffer = cp;
	req->ktr_header.ktr_len = uap->len;
	ktr_submitrequest(td, req);
	return (0);
#else /* !KTRACE */
	return (ENOSYS);
#endif /* KTRACE */
}
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
typedef  int uint64_t ;
struct kevent32 {int data1; int data2; int* ext64; } ;
struct kevent {int data; int* ext; } ;
struct freebsd32_kevent_args {int eventlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP (struct kevent,struct kevent32,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int KQ_NEVENTS ; 
 int /*<<< orphan*/  PTROUT_CP (struct kevent,struct kevent32,int /*<<< orphan*/ ) ; 
 int copyout (struct kevent32*,int,int) ; 
 int /*<<< orphan*/  fflags ; 
 int /*<<< orphan*/  filter ; 
 int /*<<< orphan*/  flags ; 
 int /*<<< orphan*/  ident ; 
 int nitems (int*) ; 
 int /*<<< orphan*/  udata ; 

__attribute__((used)) static int
freebsd32_kevent_copyout(void *arg, struct kevent *kevp, int count)
{
	struct freebsd32_kevent_args *uap;
	struct kevent32	ks32[KQ_NEVENTS];
	uint64_t e;
	int i, j, error;

	KASSERT(count <= KQ_NEVENTS, ("count (%d) > KQ_NEVENTS", count));
	uap = (struct freebsd32_kevent_args *)arg;

	for (i = 0; i < count; i++) {
		CP(kevp[i], ks32[i], ident);
		CP(kevp[i], ks32[i], filter);
		CP(kevp[i], ks32[i], flags);
		CP(kevp[i], ks32[i], fflags);
#if BYTE_ORDER == LITTLE_ENDIAN
		ks32[i].data1 = kevp[i].data;
		ks32[i].data2 = kevp[i].data >> 32;
#else
		ks32[i].data1 = kevp[i].data >> 32;
		ks32[i].data2 = kevp[i].data;
#endif
		PTROUT_CP(kevp[i], ks32[i], udata);
		for (j = 0; j < nitems(kevp->ext); j++) {
			e = kevp[i].ext[j];
#if BYTE_ORDER == LITTLE_ENDIAN
			ks32[i].ext64[2 * j] = e;
			ks32[i].ext64[2 * j + 1] = e >> 32;
#else
			ks32[i].ext64[2 * j] = e >> 32;
			ks32[i].ext64[2 * j + 1] = e;
#endif
		}
	}
	error = copyout(ks32, uap->eventlist, count * sizeof *ks32);
	if (error == 0)
		uap->eventlist += count;
	return (error);
}
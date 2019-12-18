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
typedef  int u_int ;
struct timeval {scalar_t__ tv_sec; int tv_usec; } ;
struct thread {scalar_t__* td_retval; TYPE_1__* td_proc; } ;
struct filedesc {int fd_lastfile; } ;
typedef  int sbintime_t ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  fd_mask ;
struct TYPE_2__ {struct filedesc* p_fd; } ;

/* Variables and functions */
 int EINTR ; 
 int EINVAL ; 
 int ERESTART ; 
 int EWOULDBLOCK ; 
 scalar_t__ INT32_MAX ; 
 int /*<<< orphan*/  M_SELECT ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int NBBY ; 
 int NFDBITS ; 
 int SBT_MAX ; 
 scalar_t__ TIMESEL (int*,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getbits (int /*<<< orphan*/ *,int) ; 
 int howmany (int,int) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putbits (int /*<<< orphan*/ *,int) ; 
 int roundup (int,int) ; 
 int select_check_badfd (int /*<<< orphan*/ *,int,int,int) ; 
 int selrescan (struct thread*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int selscan (struct thread*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  seltdclear (struct thread*) ; 
 int /*<<< orphan*/  seltdinit (struct thread*) ; 
 int seltdwait (struct thread*,int,int) ; 
 int /*<<< orphan*/  swizzle_fdset (int /*<<< orphan*/ *) ; 
 int tc_precexp ; 
 scalar_t__ tc_tick_sbt ; 
 int /*<<< orphan*/  timevalisset (struct timeval*) ; 
 int tvtosbt (struct timeval) ; 

int
kern_select(struct thread *td, int nd, fd_set *fd_in, fd_set *fd_ou,
    fd_set *fd_ex, struct timeval *tvp, int abi_nfdbits)
{
	struct filedesc *fdp;
	/*
	 * The magic 2048 here is chosen to be just enough for FD_SETSIZE
	 * infds with the new FD_SETSIZE of 1024, and more than enough for
	 * FD_SETSIZE infds, outfds and exceptfds with the old FD_SETSIZE
	 * of 256.
	 */
	fd_mask s_selbits[howmany(2048, NFDBITS)];
	fd_mask *ibits[3], *obits[3], *selbits, *sbp;
	struct timeval rtv;
	sbintime_t asbt, precision, rsbt;
	u_int nbufbytes, ncpbytes, ncpubytes, nfdbits;
	int error, lf, ndu;

	if (nd < 0)
		return (EINVAL);
	fdp = td->td_proc->p_fd;
	ndu = nd;
	lf = fdp->fd_lastfile;
	if (nd > lf + 1)
		nd = lf + 1;

	error = select_check_badfd(fd_in, nd, ndu, abi_nfdbits);
	if (error != 0)
		return (error);
	error = select_check_badfd(fd_ou, nd, ndu, abi_nfdbits);
	if (error != 0)
		return (error);
	error = select_check_badfd(fd_ex, nd, ndu, abi_nfdbits);
	if (error != 0)
		return (error);

	/*
	 * Allocate just enough bits for the non-null fd_sets.  Use the
	 * preallocated auto buffer if possible.
	 */
	nfdbits = roundup(nd, NFDBITS);
	ncpbytes = nfdbits / NBBY;
	ncpubytes = roundup(nd, abi_nfdbits) / NBBY;
	nbufbytes = 0;
	if (fd_in != NULL)
		nbufbytes += 2 * ncpbytes;
	if (fd_ou != NULL)
		nbufbytes += 2 * ncpbytes;
	if (fd_ex != NULL)
		nbufbytes += 2 * ncpbytes;
	if (nbufbytes <= sizeof s_selbits)
		selbits = &s_selbits[0];
	else
		selbits = malloc(nbufbytes, M_SELECT, M_WAITOK);

	/*
	 * Assign pointers into the bit buffers and fetch the input bits.
	 * Put the output buffers together so that they can be bzeroed
	 * together.
	 */
	sbp = selbits;
#define	getbits(name, x) \
	do {								\
		if (name == NULL) {					\
			ibits[x] = NULL;				\
			obits[x] = NULL;				\
		} else {						\
			ibits[x] = sbp + nbufbytes / 2 / sizeof *sbp;	\
			obits[x] = sbp;					\
			sbp += ncpbytes / sizeof *sbp;			\
			error = copyin(name, ibits[x], ncpubytes);	\
			if (error != 0)					\
				goto done;				\
			if (ncpbytes != ncpubytes)			\
				bzero((char *)ibits[x] + ncpubytes,	\
				    ncpbytes - ncpubytes);		\
		}							\
	} while (0)
	getbits(fd_in, 0);
	getbits(fd_ou, 1);
	getbits(fd_ex, 2);
#undef	getbits

#if BYTE_ORDER == BIG_ENDIAN && defined(__LP64__)
	/*
	 * XXX: swizzle_fdset assumes that if abi_nfdbits != NFDBITS,
	 * we are running under 32-bit emulation. This should be more
	 * generic.
	 */
#define swizzle_fdset(bits)						\
	if (abi_nfdbits != NFDBITS && bits != NULL) {			\
		int i;							\
		for (i = 0; i < ncpbytes / sizeof *sbp; i++)		\
			bits[i] = (bits[i] >> 32) | (bits[i] << 32);	\
	}
#else
#define swizzle_fdset(bits)
#endif

	/* Make sure the bit order makes it through an ABI transition */
	swizzle_fdset(ibits[0]);
	swizzle_fdset(ibits[1]);
	swizzle_fdset(ibits[2]);
	
	if (nbufbytes != 0)
		bzero(selbits, nbufbytes / 2);

	precision = 0;
	if (tvp != NULL) {
		rtv = *tvp;
		if (rtv.tv_sec < 0 || rtv.tv_usec < 0 ||
		    rtv.tv_usec >= 1000000) {
			error = EINVAL;
			goto done;
		}
		if (!timevalisset(&rtv))
			asbt = 0;
		else if (rtv.tv_sec <= INT32_MAX) {
			rsbt = tvtosbt(rtv);
			precision = rsbt;
			precision >>= tc_precexp;
			if (TIMESEL(&asbt, rsbt))
				asbt += tc_tick_sbt;
			if (asbt <= SBT_MAX - rsbt)
				asbt += rsbt;
			else
				asbt = -1;
		} else
			asbt = -1;
	} else
		asbt = -1;
	seltdinit(td);
	/* Iterate until the timeout expires or descriptors become ready. */
	for (;;) {
		error = selscan(td, ibits, obits, nd);
		if (error || td->td_retval[0] != 0)
			break;
		error = seltdwait(td, asbt, precision);
		if (error)
			break;
		error = selrescan(td, ibits, obits);
		if (error || td->td_retval[0] != 0)
			break;
	}
	seltdclear(td);

done:
	/* select is not restarted after signals... */
	if (error == ERESTART)
		error = EINTR;
	if (error == EWOULDBLOCK)
		error = 0;

	/* swizzle bit order back, if necessary */
	swizzle_fdset(obits[0]);
	swizzle_fdset(obits[1]);
	swizzle_fdset(obits[2]);
#undef swizzle_fdset

#define	putbits(name, x) \
	if (name && (error2 = copyout(obits[x], name, ncpubytes))) \
		error = error2;
	if (error == 0) {
		int error2;

		putbits(fd_in, 0);
		putbits(fd_ou, 1);
		putbits(fd_ex, 2);
#undef putbits
	}
	if (selbits != &s_selbits[0])
		free(selbits, M_SELECT);

	return (error);
}
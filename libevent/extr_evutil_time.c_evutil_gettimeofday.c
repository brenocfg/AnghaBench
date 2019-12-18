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
struct timezone {int dummy; } ;
struct timeval {long tv_sec; long tv_usec; } ;
typedef  int ev_uint64_t ;
typedef  int /*<<< orphan*/  FILETIME ;

/* Variables and functions */
 int EPOCH_BIAS ; 
 scalar_t__ EVUTIL_UNLIKELY (int) ; 
 int /*<<< orphan*/  GetSystemTimeAsFileTime (int /*<<< orphan*/ *) ; 
 int UNITS_PER_SEC ; 
 int UNITS_PER_USEC ; 
 int USEC_PER_SEC ; 

int
evutil_gettimeofday(struct timeval *tv, struct timezone *tz)
{
#ifdef _MSC_VER
#define U64_LITERAL(n) n##ui64
#else
#define U64_LITERAL(n) n##llu
#endif

	/* Conversion logic taken from Tor, which in turn took it
	 * from Perl.  GetSystemTimeAsFileTime returns its value as
	 * an unaligned (!) 64-bit value containing the number of
	 * 100-nanosecond intervals since 1 January 1601 UTC. */
#define EPOCH_BIAS U64_LITERAL(116444736000000000)
#define UNITS_PER_SEC U64_LITERAL(10000000)
#define USEC_PER_SEC U64_LITERAL(1000000)
#define UNITS_PER_USEC U64_LITERAL(10)
	union {
		FILETIME ft_ft;
		ev_uint64_t ft_64;
	} ft;

	if (tv == NULL)
		return -1;

	GetSystemTimeAsFileTime(&ft.ft_ft);

	if (EVUTIL_UNLIKELY(ft.ft_64 < EPOCH_BIAS)) {
		/* Time before the unix epoch. */
		return -1;
	}
	ft.ft_64 -= EPOCH_BIAS;
	tv->tv_sec = (long) (ft.ft_64 / UNITS_PER_SEC);
	tv->tv_usec = (long) ((ft.ft_64 / UNITS_PER_USEC) % USEC_PER_SEC);
	return 0;
}
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

/* Variables and functions */
 int SIGRTMIN ; 
 int /*<<< orphan*/  asc ; 
 int /*<<< orphan*/  memcpy (int*,int const*,size_t) ; 
 int /*<<< orphan*/  qsort (int*,size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
sigorder(int *ordered, const int *tosend, size_t len)
{
	memcpy(ordered, tosend, len * sizeof(*tosend));
	qsort(ordered, len, sizeof(*ordered), asc);
	if (len == 1)
		return len;

#ifdef __FreeBSD__
	/*
	 * Don't dedupe signal numbers (bug 212173)
	 *
	 * Per kib's comment..
	 *
	 * "
	 * OTOH, FreeBSD behaviour is to treat all signals as realtime while
	 * there is no mem shortage and siginfo can be allocated.  In
	 * particular, signals < SIGRTMIN are not collapsed when queued more
	 * than once.
	 * "
	 */

	return len;
#else

	size_t i, j;
	for (i = 0, j = 0; i < len - 1; i++) {
		if (ordered[i] >= SIGRTMIN)
			continue;
		if (j == 0)
			j = i + 1;
		while (ordered[i] == ordered[j] && j < len)
			j++;
		if (j == len)
			break;
		ordered[i + 1] = ordered[j];
	}
	return i + 1;
#endif
}
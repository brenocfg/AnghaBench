#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  pid ;
typedef  int /*<<< orphan*/  isc_time_t ;
struct TYPE_4__ {int initcount; } ;
typedef  TYPE_1__ isc_entropy_t ;

/* Variables and functions */
 int /*<<< orphan*/  TIME_NOW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  entropypool_adddata (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  getppid () ; 

__attribute__((used)) static inline void
reseed(isc_entropy_t *ent) {
	isc_time_t t;
	pid_t pid;

	if (ent->initcount == 0) {
		pid = getpid();
		entropypool_adddata(ent, &pid, sizeof(pid), 0);
		pid = getppid();
		entropypool_adddata(ent, &pid, sizeof(pid), 0);
	}

	/*!
	 * After we've reseeded 100 times, only add new timing info every
	 * 50 requests.  This will keep us from using lots and lots of
	 * CPU just to return bad pseudorandom data anyway.
	 */
	if (ent->initcount > 100)
		if ((ent->initcount % 50) != 0)
			return;

	TIME_NOW(&t);
	entropypool_adddata(ent, &t, sizeof(t), 0);
	ent->initcount++;
}
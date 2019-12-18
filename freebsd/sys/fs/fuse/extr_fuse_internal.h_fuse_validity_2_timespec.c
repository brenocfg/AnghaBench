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
struct timespec {scalar_t__ tv_sec; int /*<<< orphan*/  tv_nsec; } ;
struct fuse_entry_out {scalar_t__ entry_valid; int /*<<< orphan*/  entry_valid_nsec; } ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  getnanouptime (struct timespec*) ; 
 int /*<<< orphan*/  timespecadd (struct timespec*,struct timespec*,struct timespec*) ; 

__attribute__((used)) static inline void
fuse_validity_2_timespec(const struct fuse_entry_out *feo,
	struct timespec *timeout)
{
	struct timespec duration, now;

	getnanouptime(&now);
	/* "+ 2" is the bound of entry_valid_nsec + now.tv_nsec */
	if (feo->entry_valid >= INT_MAX ||
	    feo->entry_valid + now.tv_sec + 2 >= INT_MAX) {
		timeout->tv_sec = INT_MAX;
	} else {
		duration.tv_sec = feo->entry_valid;
		duration.tv_nsec = feo->entry_valid_nsec;
		timespecadd(&duration, &now, timeout);
	}
}
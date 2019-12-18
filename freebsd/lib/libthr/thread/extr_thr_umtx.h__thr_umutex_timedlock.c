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
typedef  int /*<<< orphan*/  uint32_t ;
struct umutex {int dummy; } ;
struct timespec {int dummy; } ;

/* Variables and functions */
 int __thr_umutex_timedlock (struct umutex*,int /*<<< orphan*/ ,struct timespec const*) ; 
 scalar_t__ _thr_umutex_trylock2 (struct umutex*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
_thr_umutex_timedlock(struct umutex *mtx, uint32_t id,
    const struct timespec *timeout)
{

	if (_thr_umutex_trylock2(mtx, id) == 0)
		return (0);
	return (__thr_umutex_timedlock(mtx, id, timeout));
}
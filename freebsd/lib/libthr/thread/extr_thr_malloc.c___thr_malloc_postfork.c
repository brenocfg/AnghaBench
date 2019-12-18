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
struct pthread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TID (struct pthread*) ; 
 int /*<<< orphan*/  _thr_umutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thr_malloc_umtx ; 

void
__thr_malloc_postfork(struct pthread *curthread)
{

	_thr_umutex_unlock(&thr_malloc_umtx, TID(curthread));
}
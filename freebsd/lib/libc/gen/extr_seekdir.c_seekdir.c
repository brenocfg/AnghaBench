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
struct TYPE_4__ {int /*<<< orphan*/  dd_lock; } ;
typedef  TYPE_1__ DIR ;

/* Variables and functions */
 scalar_t__ __isthreaded ; 
 int /*<<< orphan*/  _pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _seekdir (TYPE_1__*,long) ; 

void
seekdir(DIR *dirp, long loc)
{
	if (__isthreaded)
		_pthread_mutex_lock(&dirp->dd_lock);
	_seekdir(dirp, loc);
	if (__isthreaded)
		_pthread_mutex_unlock(&dirp->dd_lock);
}
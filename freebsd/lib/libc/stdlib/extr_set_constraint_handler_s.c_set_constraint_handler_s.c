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
typedef  int /*<<< orphan*/ * constraint_handler_t ;

/* Variables and functions */
 scalar_t__ __isthreaded ; 
 int /*<<< orphan*/ ** _ch ; 
 int /*<<< orphan*/  _pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ch_lock ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** malloc (int) ; 

constraint_handler_t
set_constraint_handler_s(constraint_handler_t handler)
{
	constraint_handler_t *new, *old, ret;

	new = malloc(sizeof(constraint_handler_t));
	if (new == NULL)
		return (NULL);
	*new = handler;
	if (__isthreaded)
		_pthread_mutex_lock(&ch_lock);
	old = _ch;
	_ch = new;
	if (__isthreaded)
		_pthread_mutex_unlock(&ch_lock);
	if (old == NULL) {
		ret = NULL;
	} else {
		ret = *old;
		free(old);
	}
	return (ret);
}
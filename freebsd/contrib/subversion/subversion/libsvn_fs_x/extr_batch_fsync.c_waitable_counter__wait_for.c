#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int value; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; } ;
typedef  TYPE_1__ waitable_counter_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  svn_mutex__lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_mutex__unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_thread_cond__wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
waitable_counter__wait_for(waitable_counter_t *counter,
                           int value)
{
  svn_boolean_t done = FALSE;

  /* This loop implicitly handles spurious wake-ups. */
  do
    {
      SVN_ERR(svn_mutex__lock(counter->mutex));

      if (counter->value == value)
        done = TRUE;
      else
        SVN_ERR(svn_thread_cond__wait(counter->cond, counter->mutex));

      SVN_ERR(svn_mutex__unlock(counter->mutex, SVN_NO_ERROR));
    }
  while (!done);

  return SVN_NO_ERROR;
}
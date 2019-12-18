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
struct TYPE_3__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ waitable_counter_t ;
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_mutex__lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_mutex__unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_thread_cond__broadcast (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
waitable_counter__increment(waitable_counter_t *counter)
{
  SVN_ERR(svn_mutex__lock(counter->mutex));
  counter->value++;

  SVN_ERR(svn_thread_cond__broadcast(counter->cond));
  SVN_ERR(svn_mutex__unlock(counter->mutex, SVN_NO_ERROR));

  return SVN_NO_ERROR;
}
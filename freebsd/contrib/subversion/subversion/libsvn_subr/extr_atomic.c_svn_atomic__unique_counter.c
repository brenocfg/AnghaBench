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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_MUTEX__WITH_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  counter_mutex ; 
 int /*<<< orphan*/  counter_status ; 
 int /*<<< orphan*/  init_unique_counter ; 
 int /*<<< orphan*/  read_unique_counter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_atomic__init_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_atomic__unique_counter(apr_uint64_t *value)
{
  SVN_ERR(svn_atomic__init_once(&counter_status, init_unique_counter, NULL,
                                NULL));
  SVN_MUTEX__WITH_LOCK(counter_mutex, read_unique_counter(value));
  return SVN_NO_ERROR;
}
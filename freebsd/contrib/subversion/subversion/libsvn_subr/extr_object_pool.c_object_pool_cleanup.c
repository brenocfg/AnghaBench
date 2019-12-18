#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ object_count; scalar_t__ unused_count; } ;
typedef  TYPE_1__ svn_object_pool__t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int) ; 

__attribute__((used)) static apr_status_t
object_pool_cleanup(void *baton)
{
  svn_object_pool__t *object_pool = baton;

  /* all entries must have been released up by now */
  SVN_ERR_ASSERT_NO_RETURN(   object_pool->object_count
                           == object_pool->unused_count);

  return APR_SUCCESS;
}
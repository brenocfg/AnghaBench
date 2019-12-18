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
struct TYPE_3__ {scalar_t__ bdb; } ;
typedef  TYPE_1__ bdb_env_baton_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_bdb__close (TYPE_1__*) ; 

__attribute__((used)) static apr_status_t
cleanup_env_baton(void *data)
{
  bdb_env_baton_t *bdb_baton = data;

  if (bdb_baton->bdb)
    svn_error_clear(svn_fs_bdb__close(bdb_baton));

  return APR_SUCCESS;
}
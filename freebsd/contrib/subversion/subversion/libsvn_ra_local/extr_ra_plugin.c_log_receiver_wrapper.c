#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  callback_baton; TYPE_1__* callbacks; } ;
typedef  TYPE_2__ svn_ra_local__session_baton_t ;
struct TYPE_8__ {int /*<<< orphan*/ * changed_paths2; int /*<<< orphan*/ * changed_paths; } ;
typedef  TYPE_3__ svn_log_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct log_baton {int /*<<< orphan*/  real_baton; int /*<<< orphan*/ * (* real_cb ) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ;TYPE_2__* sess; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* cancel_func ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub2 (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
log_receiver_wrapper(void *baton,
                     svn_log_entry_t *log_entry,
                     apr_pool_t *pool)
{
  struct log_baton *b = baton;
  svn_ra_local__session_baton_t *sess = b->sess;

  if (sess->callbacks->cancel_func)
    SVN_ERR((sess->callbacks->cancel_func)(sess->callback_baton));

  /* For consistency with the other RA layers, replace an empty
     changed-paths hash with a NULL one.

     ### Should this be done by svn_ra_get_log2() instead, then? */
  if ((log_entry->changed_paths2)
      && (apr_hash_count(log_entry->changed_paths2) == 0))
    {
      log_entry->changed_paths = NULL;
      log_entry->changed_paths2 = NULL;
    }

  return b->real_cb(b->real_baton, log_entry, pool);
}
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
struct TYPE_3__ {int /*<<< orphan*/  revision; int /*<<< orphan*/  changed_paths2; int /*<<< orphan*/  revprops; } ;
typedef  TYPE_1__ svn_log_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct log_wrapper_baton {int /*<<< orphan*/  baton; int /*<<< orphan*/ * (* receiver ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,char const*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_compat_log_revprops_out (char const**,char const**,char const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
log_wrapper_callback(void *baton,
                     svn_log_entry_t *log_entry,
                     apr_pool_t *pool)
{
  struct log_wrapper_baton *lwb = baton;

  if (lwb->receiver && SVN_IS_VALID_REVNUM(log_entry->revision))
    {
      const char *author, *date, *message;
      svn_compat_log_revprops_out(&author, &date, &message,
                                  log_entry->revprops);
      return lwb->receiver(lwb->baton,
                           log_entry->changed_paths2,
                           log_entry->revision,
                           author, date, message,
                           pool);
    }

  return SVN_NO_ERROR;
}
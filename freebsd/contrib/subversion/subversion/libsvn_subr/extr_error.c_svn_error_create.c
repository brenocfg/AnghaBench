#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  message; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* make_error_internal (int /*<<< orphan*/ ,TYPE_1__*) ; 

svn_error_t *
svn_error_create(apr_status_t apr_err,
                 svn_error_t *child,
                 const char *message)
{
  svn_error_t *err;

  err = make_error_internal(apr_err, child);

  if (message)
    err->message = apr_pstrdup(err->pool, message);

  return err;
}
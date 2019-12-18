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
typedef  scalar_t__ svn_errno_t ;
struct TYPE_3__ {scalar_t__ errcode; int /*<<< orphan*/ * errdesc; } ;
typedef  TYPE_1__ err_defn ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_cpystrn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* apr_strerror (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* error_table ; 

char *
svn_strerror(apr_status_t statcode, char *buf, apr_size_t bufsize)
{
  const err_defn *defn;

  for (defn = error_table; defn->errdesc != NULL; ++defn)
    if (defn->errcode == (svn_errno_t)statcode)
      {
        apr_cpystrn(buf, _(defn->errdesc), bufsize);
        return buf;
      }

  return apr_strerror(statcode, buf, bufsize);
}
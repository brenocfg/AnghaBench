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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_diff_datasource_e ;
struct fns_wrapper_baton {int /*<<< orphan*/  old_baton; TYPE_1__* vtable; } ;
typedef  size_t apr_size_t ;
typedef  scalar_t__ apr_off_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* datasource_open ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static svn_error_t *
datasources_open(void *baton,
                 apr_off_t *prefix_lines,
                 apr_off_t *suffix_lines,
                 const svn_diff_datasource_e *datasources,
                 apr_size_t datasource_len)
{
  struct fns_wrapper_baton *fwb = baton;
  apr_size_t i;

  /* Just iterate over the datasources, using the old singular version. */
  for (i = 0; i < datasource_len; i++)
    {
      SVN_ERR(fwb->vtable->datasource_open(fwb->old_baton, datasources[i]));
    }

  /* Don't claim any prefix or suffix matches. */
  *prefix_lines = 0;
  *suffix_lines = 0;

  return SVN_NO_ERROR;
}
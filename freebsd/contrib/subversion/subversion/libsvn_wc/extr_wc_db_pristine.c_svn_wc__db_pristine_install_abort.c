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
struct TYPE_3__ {int /*<<< orphan*/  inner_stream; } ;
typedef  TYPE_1__ svn_wc__db_install_data_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream__install_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_pristine_install_abort(svn_wc__db_install_data_t *install_data,
                                  apr_pool_t *scratch_pool)
{
  return svn_error_trace(svn_stream__install_delete(install_data->inner_stream,
                                                    scratch_pool));
}
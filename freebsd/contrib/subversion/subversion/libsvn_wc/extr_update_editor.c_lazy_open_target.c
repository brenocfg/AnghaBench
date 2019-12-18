#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc__db_install_data_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct handler_baton {int /*<<< orphan*/ * install_data; TYPE_2__* fb; int /*<<< orphan*/  new_text_base_sha1_checksum; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_6__ {int /*<<< orphan*/  local_abspath; } ;
struct TYPE_5__ {TYPE_3__* dir_baton; TYPE_1__* edit_baton; } ;
struct TYPE_4__ {int /*<<< orphan*/  db; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_wc__db_pristine_prepare_install (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
lazy_open_target(svn_stream_t **stream,
                 void *baton,
                 apr_pool_t *result_pool,
                 apr_pool_t *scratch_pool)
{
  struct handler_baton *hb = baton;
  svn_wc__db_install_data_t *install_data;

  /* By convention return value is undefined on error, but we rely
     on HB->INSTALL_DATA value in window_handler() and abort
     INSTALL_STREAM if is not NULL on error.
     So we store INSTALL_DATA to local variable first, to leave
     HB->INSTALL_DATA unchanged on error. */
  SVN_ERR(svn_wc__db_pristine_prepare_install(stream,
                                              &install_data,
                                              &hb->new_text_base_sha1_checksum,
                                              NULL,
                                              hb->fb->edit_baton->db,
                                              hb->fb->dir_baton->local_abspath,
                                              result_pool, scratch_pool));

  hb->install_data = install_data;

  return SVN_NO_ERROR;
}
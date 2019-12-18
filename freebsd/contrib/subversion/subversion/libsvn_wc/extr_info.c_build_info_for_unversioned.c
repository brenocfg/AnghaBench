#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* recorded_size; int /*<<< orphan*/  depth; void* copyfrom_rev; } ;
typedef  TYPE_1__ svn_wc_info_t ;
struct TYPE_5__ {TYPE_1__* wc_info; int /*<<< orphan*/ * lock; int /*<<< orphan*/ * last_changed_author; scalar_t__ last_changed_date; void* last_changed_rev; void* size; int /*<<< orphan*/  kind; void* rev; int /*<<< orphan*/ * repos_root_URL; int /*<<< orphan*/ * repos_UUID; int /*<<< orphan*/ * URL; } ;
typedef  TYPE_2__ svn_wc__info2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* SVN_INVALID_FILESIZE ; 
 void* SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_depth_unknown ; 
 int /*<<< orphan*/  svn_node_none ; 

__attribute__((used)) static svn_error_t *
build_info_for_unversioned(svn_wc__info2_t **info,
                           apr_pool_t *pool)
{
  svn_wc__info2_t *tmpinfo = apr_pcalloc(pool, sizeof(*tmpinfo));
  svn_wc_info_t *wc_info = apr_pcalloc(pool, sizeof (*wc_info));

  tmpinfo->URL                  = NULL;
  tmpinfo->repos_UUID           = NULL;
  tmpinfo->repos_root_URL       = NULL;
  tmpinfo->rev                  = SVN_INVALID_REVNUM;
  tmpinfo->kind                 = svn_node_none;
  tmpinfo->size                 = SVN_INVALID_FILESIZE;
  tmpinfo->last_changed_rev     = SVN_INVALID_REVNUM;
  tmpinfo->last_changed_date    = 0;
  tmpinfo->last_changed_author  = NULL;
  tmpinfo->lock                 = NULL;

  tmpinfo->wc_info = wc_info;

  wc_info->copyfrom_rev = SVN_INVALID_REVNUM;
  wc_info->depth = svn_depth_unknown;
  wc_info->recorded_size = SVN_INVALID_FILESIZE;

  *info = tmpinfo;
  return SVN_NO_ERROR;
}
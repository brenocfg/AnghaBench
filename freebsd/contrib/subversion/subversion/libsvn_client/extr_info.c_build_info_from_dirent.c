#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_lock_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_8__ {int /*<<< orphan*/  size; int /*<<< orphan*/  last_author; int /*<<< orphan*/  time; int /*<<< orphan*/  created_rev; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ svn_dirent_t ;
struct TYPE_9__ {int /*<<< orphan*/ * wc_info; int /*<<< orphan*/  size; int /*<<< orphan*/ * lock; int /*<<< orphan*/  last_changed_author; int /*<<< orphan*/  last_changed_date; int /*<<< orphan*/  last_changed_rev; int /*<<< orphan*/  repos_root_URL; int /*<<< orphan*/  repos_UUID; int /*<<< orphan*/  kind; int /*<<< orphan*/  rev; int /*<<< orphan*/  URL; } ;
typedef  TYPE_2__ svn_client_info2_t ;
struct TYPE_10__ {int /*<<< orphan*/  repos_root_url; int /*<<< orphan*/  repos_uuid; int /*<<< orphan*/  rev; int /*<<< orphan*/  url; } ;
typedef  TYPE_3__ svn_client__pathrev_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_2__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static svn_error_t *
build_info_from_dirent(svn_client_info2_t **info,
                       const svn_dirent_t *dirent,
                       svn_lock_t *lock,
                       const svn_client__pathrev_t *pathrev,
                       apr_pool_t *pool)
{
  svn_client_info2_t *tmpinfo = apr_pcalloc(pool, sizeof(*tmpinfo));

  tmpinfo->URL                  = pathrev->url;
  tmpinfo->rev                  = pathrev->rev;
  tmpinfo->kind                 = dirent->kind;
  tmpinfo->repos_UUID           = pathrev->repos_uuid;
  tmpinfo->repos_root_URL       = pathrev->repos_root_url;
  tmpinfo->last_changed_rev     = dirent->created_rev;
  tmpinfo->last_changed_date    = dirent->time;
  tmpinfo->last_changed_author  = dirent->last_author;
  tmpinfo->lock                 = lock;
  tmpinfo->size                 = dirent->size;

  tmpinfo->wc_info              = NULL;

  *info = tmpinfo;
  return SVN_NO_ERROR;
}
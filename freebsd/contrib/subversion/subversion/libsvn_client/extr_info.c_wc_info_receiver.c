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
struct TYPE_6__ {int /*<<< orphan*/  client_receiver_baton; int /*<<< orphan*/ * (* client_receiver_func ) (int /*<<< orphan*/ ,char const*,TYPE_3__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ wc_info_receiver_baton_t ;
struct TYPE_7__ {int /*<<< orphan*/  wc_info; int /*<<< orphan*/  lock; int /*<<< orphan*/  last_changed_author; int /*<<< orphan*/  last_changed_date; int /*<<< orphan*/  last_changed_rev; int /*<<< orphan*/  size; int /*<<< orphan*/  kind; int /*<<< orphan*/  URL; int /*<<< orphan*/  rev; int /*<<< orphan*/  repos_UUID; int /*<<< orphan*/  repos_root_URL; } ;
typedef  TYPE_2__ svn_wc__info2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_8__ {int /*<<< orphan*/  wc_info; int /*<<< orphan*/  lock; int /*<<< orphan*/  last_changed_author; int /*<<< orphan*/  last_changed_date; int /*<<< orphan*/  last_changed_rev; int /*<<< orphan*/  size; int /*<<< orphan*/  kind; int /*<<< orphan*/  URL; int /*<<< orphan*/  rev; int /*<<< orphan*/  repos_UUID; int /*<<< orphan*/  repos_root_URL; } ;
typedef  TYPE_3__ svn_client_info2_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,char const*,TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
wc_info_receiver(void *baton,
                 const char *abspath_or_url,
                 const svn_wc__info2_t *wc_info,
                 apr_pool_t *scratch_pool)
{
  wc_info_receiver_baton_t *b = baton;
  svn_client_info2_t client_info;

  /* Make a shallow copy in CLIENT_INFO of the contents of WC_INFO. */
  client_info.repos_root_URL = wc_info->repos_root_URL;
  client_info.repos_UUID = wc_info->repos_UUID;
  client_info.rev = wc_info->rev;
  client_info.URL = wc_info->URL;

  client_info.kind = wc_info->kind;
  client_info.size = wc_info->size;
  client_info.last_changed_rev = wc_info->last_changed_rev;
  client_info.last_changed_date = wc_info->last_changed_date;
  client_info.last_changed_author = wc_info->last_changed_author;

  client_info.lock = wc_info->lock;

  client_info.wc_info = wc_info->wc_info;

  return b->client_receiver_func(b->client_receiver_baton,
                                 abspath_or_url, &client_info, scratch_pool);
}
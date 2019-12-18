#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * uuid; int /*<<< orphan*/ * fsap_data; int /*<<< orphan*/ * vtable; int /*<<< orphan*/ * access_ctx; int /*<<< orphan*/ * config; int /*<<< orphan*/ * warning_baton; int /*<<< orphan*/  warning; int /*<<< orphan*/ * path; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  default_warning_func ; 

__attribute__((used)) static svn_fs_t *
fs_new(apr_hash_t *fs_config, apr_pool_t *pool)
{
  svn_fs_t *fs = apr_palloc(pool, sizeof(*fs));
  fs->pool = pool;
  fs->path = NULL;
  fs->warning = default_warning_func;
  fs->warning_baton = NULL;
  fs->config = fs_config;
  fs->access_ctx = NULL;
  fs->vtable = NULL;
  fs->fsap_data = NULL;
  fs->uuid = NULL;
  return fs;
}
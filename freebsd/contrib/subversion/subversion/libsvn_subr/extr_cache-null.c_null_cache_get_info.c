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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {scalar_t__ total_size; scalar_t__ data_size; scalar_t__ used_size; scalar_t__ total_entries; scalar_t__ used_entries; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ svn_cache__info_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static svn_error_t *
null_cache_get_info(void *cache_void,
                    svn_cache__info_t *info,
                    svn_boolean_t reset,
                    apr_pool_t *result_pool)
{
  const char *id = cache_void;

  info->id = apr_pstrdup(result_pool, id);

  info->used_entries = 0;
  info->total_entries = 0;

  info->used_size = 0;
  info->data_size = 0;
  info->total_size = 0;

  return SVN_NO_ERROR;
}
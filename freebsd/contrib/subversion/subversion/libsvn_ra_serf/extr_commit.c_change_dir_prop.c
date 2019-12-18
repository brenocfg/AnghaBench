#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ svn_prop_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {int /*<<< orphan*/  prop_changes; int /*<<< orphan*/  pool; int /*<<< orphan*/  commit_ctx; } ;
typedef  TYPE_2__ dir_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  USING_HTTPV2_COMMIT_SUPPORT (int /*<<< orphan*/ ) ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  checkout_dir (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  svn_string_dup (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
change_dir_prop(void *dir_baton,
                const char *name,
                const svn_string_t *value,
                apr_pool_t *scratch_pool)
{
  dir_context_t *dir = dir_baton;
  svn_prop_t *prop;

  if (! USING_HTTPV2_COMMIT_SUPPORT(dir->commit_ctx))
    {
      /* Ensure we have a checked out dir. */
      SVN_ERR(checkout_dir(dir, scratch_pool));
    }

  prop = apr_palloc(dir->pool, sizeof(*prop));

  prop->name = apr_pstrdup(dir->pool, name);
  prop->value = svn_string_dup(value, dir->pool);

  svn_hash_sets(dir->prop_changes, prop->name, prop);

  return SVN_NO_ERROR;
}
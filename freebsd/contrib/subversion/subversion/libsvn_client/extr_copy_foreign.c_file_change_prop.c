#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  scalar_t__ svn_prop_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct file_baton_t {int /*<<< orphan*/  pool; scalar_t__ properties; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_MERGEINFO ; 
 scalar_t__ apr_hash_make (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_prop_regular_kind ; 
 scalar_t__ svn_property_kind2 (char const*) ; 
 int /*<<< orphan*/  svn_string_dup (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
file_change_prop(void *file_baton,
                 const char *name,
                 const svn_string_t *value,
                 apr_pool_t *scratch_pool)
{
  struct file_baton_t *fb = file_baton;
  svn_prop_kind_t prop_kind;

  prop_kind = svn_property_kind2(name);

  if (prop_kind != svn_prop_regular_kind
      || ! strcmp(name, SVN_PROP_MERGEINFO))
    {
      /* We can't handle DAV, ENTRY and merge specific props here */
      return SVN_NO_ERROR;
    }

  /* We store all properties in the hash for immediate addition
      with the svn_wc_add_from_disk3() call */
  if (! fb->properties)
    fb->properties = apr_hash_make(fb->pool);

  if (value != NULL)
    svn_hash_sets(fb->properties, apr_pstrdup(fb->pool, name),
                  svn_string_dup(value, fb->pool));

  return SVN_NO_ERROR;
}
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
typedef  int /*<<< orphan*/  svn_error_t ;
struct revision_baton_t {int /*<<< orphan*/  props; int /*<<< orphan*/  rev_orig; } ;
struct node_baton_t {int /*<<< orphan*/  props; scalar_t__ has_props; int /*<<< orphan*/  node_path; scalar_t__ has_prop_delta; scalar_t__ do_skip; struct revision_baton_t* rb; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_STREAM_MALFORMED_DATA ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_MERGEINFO ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  adjust_mergeinfo (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,struct revision_baton_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_pool_get (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_prop_to_stringbuf (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static svn_error_t *
set_node_property(void *node_baton,
                  const char *name,
                  const svn_string_t *value)
{
  struct node_baton_t *nb = node_baton;
  struct revision_baton_t *rb = nb->rb;

  if (nb->do_skip)
    return SVN_NO_ERROR;

  /* Try to detect if a delta-mode property occurs unexpectedly. HAS_PROPS
     can be false here only if the parser didn't call remove_node_props(),
     so this may indicate a bug rather than bad data. */
  if (! (nb->has_props || nb->has_prop_delta))
    return svn_error_createf(SVN_ERR_STREAM_MALFORMED_DATA, NULL,
                             _("Delta property block detected, but deltas "
                               "are not enabled for node '%s' in original "
                               "revision %ld"),
                             nb->node_path, rb->rev_orig);

  if (strcmp(name, SVN_PROP_MERGEINFO) == 0)
    {
      svn_string_t *filtered_mergeinfo;  /* Avoid compiler warning. */
      apr_pool_t *pool = apr_hash_pool_get(rb->props);
      SVN_ERR(adjust_mergeinfo(&filtered_mergeinfo, value, rb, pool));
      value = filtered_mergeinfo;
    }

  nb->has_props = TRUE;
  write_prop_to_stringbuf(nb->props, name, value);

  return SVN_NO_ERROR;
}
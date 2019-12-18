#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_prop_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct revision_baton {TYPE_2__* pb; TYPE_1__* db; int /*<<< orphan*/ * pool; } ;
struct node_baton {char const* copyfrom_path; scalar_t__ kind; char* path; scalar_t__ action; struct revision_baton* rb; int /*<<< orphan*/  is_added; int /*<<< orphan*/  copyfrom_rev; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
struct TYPE_4__ {int /*<<< orphan*/  aux_session; } ;
struct TYPE_3__ {char const* copyfrom_path; int /*<<< orphan*/  copyfrom_rev; } ;

/* Variables and functions */
 scalar_t__ ARE_VALID_COPY_ARGS (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_node_property (struct node_baton*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_action_add ; 
 scalar_t__ svn_node_action_replace ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_prop_regular_kind ; 
 scalar_t__ svn_property_kind2 (char const*) ; 
 int /*<<< orphan*/  svn_ra_get_dir2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_file (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_basename (char*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
remove_node_props(void *baton)
{
  struct node_baton *nb = baton;
  struct revision_baton *rb = nb->rb;
  apr_pool_t *pool = nb->rb->pool;
  apr_hash_index_t *hi;
  apr_hash_t *props;
  const char *orig_path;
  svn_revnum_t orig_rev;

  /* Find the path and revision that has the node's original properties */
  if (ARE_VALID_COPY_ARGS(nb->copyfrom_path, nb->copyfrom_rev))
    {
      orig_path = nb->copyfrom_path;
      orig_rev = nb->copyfrom_rev;
    }
  else if (!nb->is_added
           && ARE_VALID_COPY_ARGS(rb->db->copyfrom_path, rb->db->copyfrom_rev))
    {
      /* If this is a dir, then it's described by rb->db;
         if this is a file, then it's a child of the dir in rb->db. */
      orig_path = (nb->kind == svn_node_dir)
                    ? rb->db->copyfrom_path
                    : svn_relpath_join(rb->db->copyfrom_path,
                                       svn_relpath_basename(nb->path, NULL),
                                       rb->pool);
      orig_rev = rb->db->copyfrom_rev;
    }
  else
    {
      /* ### Should we query at a known, fixed, "head" revision number
         instead of passing SVN_INVALID_REVNUM and getting a moving target? */
      orig_path = nb->path;
      orig_rev = SVN_INVALID_REVNUM;
    }

  if ((nb->action == svn_node_action_add
            || nb->action == svn_node_action_replace)
      && ! ARE_VALID_COPY_ARGS(orig_path, orig_rev))
    /* Add-without-history; no "old" properties to worry about. */
    return SVN_NO_ERROR;

  if (nb->kind == svn_node_file)
    {
      SVN_ERR(svn_ra_get_file(nb->rb->pb->aux_session,
                              orig_path, orig_rev, NULL, NULL, &props, pool));
    }
  else  /* nb->kind == svn_node_dir */
    {
      SVN_ERR(svn_ra_get_dir2(nb->rb->pb->aux_session, NULL, NULL, &props,
                              orig_path, orig_rev, 0, pool));
    }

  for (hi = apr_hash_first(pool, props); hi; hi = apr_hash_next(hi))
    {
      const char *name = apr_hash_this_key(hi);
      svn_prop_kind_t kind = svn_property_kind2(name);

      if (kind == svn_prop_regular_kind)
        SVN_ERR(set_node_property(nb, name, NULL));
    }

  return SVN_NO_ERROR;
}
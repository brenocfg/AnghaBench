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
typedef  int /*<<< orphan*/  svn_error_t ;
struct recursive_proplist_receiver_baton {char const* anchor_abspath; char const* anchor; int /*<<< orphan*/  wrapped_receiver_baton; int /*<<< orphan*/  (* wrapped_receiver ) (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * iprops; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_skip_ancestor (char const*,char const*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
recursive_proplist_receiver(void *baton,
                            const char *local_abspath,
                            apr_hash_t *props,
                            apr_pool_t *scratch_pool)
{
  struct recursive_proplist_receiver_baton *b = baton;
  const char *path;
  apr_array_header_t *iprops = NULL;

  if (b->iprops
      && ! strcmp(local_abspath, b->anchor_abspath))
    {
      /* Report iprops with the properties for the anchor */
      iprops = b->iprops;
      b->iprops = NULL;
    }
  else if (b->iprops)
    {
      /* No report for the root?
         Report iprops anyway */

      SVN_ERR(b->wrapped_receiver(b->wrapped_receiver_baton,
                                  b->anchor ? b->anchor : b->anchor_abspath,
                                  NULL /* prop_hash */,
                                  b->iprops,
                                  scratch_pool));
      b->iprops = NULL;
    }

  /* Attempt to convert absolute paths to relative paths for
   * presentation purposes, if needed. */
  if (b->anchor && b->anchor_abspath)
    {
      path = svn_dirent_join(b->anchor,
                             svn_dirent_skip_ancestor(b->anchor_abspath,
                                                      local_abspath),
                             scratch_pool);
    }
  else
    path = local_abspath;

  return svn_error_trace(b->wrapped_receiver(b->wrapped_receiver_baton,
                                             path, props, iprops,
                                             scratch_pool));
}
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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_4__ {char* ancestor; int /*<<< orphan*/  wrapped_report_baton; TYPE_1__* wrapped_reporter; int /*<<< orphan*/  depth; } ;
typedef  TYPE_2__ report_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_3__ {int /*<<< orphan*/ * (* link_path ) (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 size_t strlen (char const*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_uri__is_ancestor (char*,char const*) ; 
 char* svn_uri_get_longest_ancestor (char const*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
reporter_link_path(void *report_baton, const char *path, const char *url,
                   svn_revnum_t revision, svn_depth_t depth,
                   svn_boolean_t start_empty,
                   const char *lock_token, apr_pool_t *pool)
{
  report_baton_t *rb = report_baton;

  if (!svn_uri__is_ancestor(rb->ancestor, url))
    {
      const char *ancestor;

      ancestor = svn_uri_get_longest_ancestor(url, rb->ancestor, pool);

      /* If we got a shorter ancestor, truncate our current ancestor.
         Note that svn_uri_get_longest_ancestor will allocate its return
         value even if it identical to one of its arguments. */

      rb->ancestor[strlen(ancestor)] = '\0';
      rb->depth = svn_depth_infinity;
    }

  return rb->wrapped_reporter->link_path(rb->wrapped_report_baton, path, url,
                                         revision, depth, start_empty,
                                         lock_token, pool);
}
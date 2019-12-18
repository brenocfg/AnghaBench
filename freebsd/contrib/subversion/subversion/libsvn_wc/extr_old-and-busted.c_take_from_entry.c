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
struct TYPE_4__ {scalar_t__ revision; scalar_t__ kind; scalar_t__ schedule; scalar_t__ uuid; scalar_t__ repos; int /*<<< orphan*/  name; scalar_t__ url; } ;
typedef  TYPE_1__ svn_wc_entry_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ SVN_INVALID_REVNUM ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_path_url_add_component2 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_schedule_add ; 
 scalar_t__ svn_wc_schedule_replace ; 

__attribute__((used)) static void
take_from_entry(const svn_wc_entry_t *src,
                svn_wc_entry_t *dst,
                apr_pool_t *pool)
{
  /* Inherits parent's revision if doesn't have a revision of one's
     own, unless this is a subdirectory. */
  if ((dst->revision == SVN_INVALID_REVNUM) && (dst->kind != svn_node_dir))
    dst->revision = src->revision;

  /* Inherits parent's url if doesn't have a url of one's own. */
  if (! dst->url)
    dst->url = svn_path_url_add_component2(src->url, dst->name, pool);

  if (! dst->repos)
    dst->repos = src->repos;

  if ((! dst->uuid)
      && (! ((dst->schedule == svn_wc_schedule_add)
             || (dst->schedule == svn_wc_schedule_replace))))
    {
      dst->uuid = src->uuid;
    }
}
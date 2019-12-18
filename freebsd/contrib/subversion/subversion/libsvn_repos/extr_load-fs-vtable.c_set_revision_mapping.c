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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  apr_hash_pool_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_palloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
set_revision_mapping(apr_hash_t *rev_map,
                     svn_revnum_t from_rev,
                     svn_revnum_t to_rev)
{
  svn_revnum_t *mapped_revs = apr_palloc(apr_hash_pool_get(rev_map),
                                         sizeof(svn_revnum_t) * 2);
  mapped_revs[0] = from_rev;
  mapped_revs[1] = to_rev;
  apr_hash_set(rev_map, mapped_revs,
               sizeof(svn_revnum_t), mapped_revs + 1);
}
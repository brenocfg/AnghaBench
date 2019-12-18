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
typedef  int /*<<< orphan*/  from_rev ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * apr_hash_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static svn_revnum_t
get_revision_mapping(apr_hash_t *rev_map,
                     svn_revnum_t from_rev)
{
  svn_revnum_t *to_rev = apr_hash_get(rev_map, &from_rev,
                                      sizeof(from_rev));
  return to_rev ? *to_rev : SVN_INVALID_REVNUM;
}
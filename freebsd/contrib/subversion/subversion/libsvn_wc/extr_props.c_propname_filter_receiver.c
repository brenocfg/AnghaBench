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
struct propname_filter_baton_t {int /*<<< orphan*/  receiver_baton; int /*<<< orphan*/  (* receiver_func ) (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  propname; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static svn_error_t *
propname_filter_receiver(void *baton,
                         const char *local_abspath,
                         apr_hash_t *props,
                         apr_pool_t *scratch_pool)
{
  struct propname_filter_baton_t *pfb = baton;
  const svn_string_t *propval = svn_hash_gets(props, pfb->propname);

  if (propval)
    {
      props = apr_hash_make(scratch_pool);
      svn_hash_sets(props, pfb->propname, propval);

      SVN_ERR(pfb->receiver_func(pfb->receiver_baton, local_abspath, props,
                                 scratch_pool));
    }

  return SVN_NO_ERROR;
}
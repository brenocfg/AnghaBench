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
typedef  int /*<<< orphan*/  (* svn_proplist_receiver2_t ) (void*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t*
call_receiver(const char *path,
              apr_hash_t *prop_hash,
              apr_array_header_t *inherited_properties,
              svn_proplist_receiver2_t receiver,
              void *receiver_baton,
              apr_pool_t *scratch_pool)
{
  if ((prop_hash && apr_hash_count(prop_hash))
      || inherited_properties)
    SVN_ERR(receiver(receiver_baton, path, prop_hash, inherited_properties,
                     scratch_pool));

  return SVN_NO_ERROR;
}
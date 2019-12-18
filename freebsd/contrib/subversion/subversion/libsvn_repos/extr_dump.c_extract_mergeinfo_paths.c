#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_2__ {int /*<<< orphan*/  pool; } ;
struct extract_mergeinfo_paths_baton {TYPE_1__ buffer; int /*<<< orphan*/  result; scalar_t__ normalize; } ;
typedef  scalar_t__ apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pmemdup (int /*<<< orphan*/ ,void const*,scalar_t__) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  normalized_unique ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_utf__normalize (char const**,void const*,scalar_t__,TYPE_1__*) ; 

__attribute__((used)) static svn_error_t *
extract_mergeinfo_paths(void *baton, const void *key, apr_ssize_t klen,
                         void *val, apr_pool_t *iterpool)
{
  struct extract_mergeinfo_paths_baton *const xb = baton;
  if (xb->normalize)
    {
      const char *normkey;
      SVN_ERR(svn_utf__normalize(&normkey, key, klen, &xb->buffer));
      svn_hash_sets(xb->result,
                    apr_pstrdup(xb->buffer.pool, normkey),
                    normalized_unique);
    }
  else
    apr_hash_set(xb->result,
                 apr_pmemdup(xb->buffer.pool, key, klen + 1), klen,
                 normalized_unique);
  return SVN_NO_ERROR;
}
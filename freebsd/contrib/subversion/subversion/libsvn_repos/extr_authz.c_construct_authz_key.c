#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int size; char* data; } ;
typedef  TYPE_1__ svn_membuf_t ;
struct TYPE_10__ {int /*<<< orphan*/  digest; } ;
typedef  TYPE_2__ svn_checksum_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int svn_checksum_size (TYPE_2__ const*) ; 
 int /*<<< orphan*/  svn_membuf__create (TYPE_1__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_membuf_t *
construct_authz_key(const svn_checksum_t *authz_key,
                    const svn_checksum_t *groups_key,
                    apr_pool_t *result_pool)
{
  svn_membuf_t *result = apr_pcalloc(result_pool, sizeof(*result));
  if (groups_key)
    {
      apr_size_t authz_size = svn_checksum_size(authz_key);
      apr_size_t groups_size = svn_checksum_size(groups_key);

      svn_membuf__create(result, authz_size + groups_size, result_pool);
      result->size = authz_size + groups_size; /* exact length is required! */

      memcpy(result->data, authz_key->digest, authz_size);
      memcpy((char *)result->data + authz_size,
             groups_key->digest, groups_size);
    }
  else
    {
      apr_size_t size = svn_checksum_size(authz_key);
      svn_membuf__create(result, size, result_pool);
      result->size = size; /* exact length is required! */
      memcpy(result->data, authz_key->digest, size);
    }

  return result;
}
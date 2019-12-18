#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  data; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ svn_membuf_t ;
struct TYPE_9__ {int /*<<< orphan*/  digest; } ;
typedef  TYPE_2__ svn_checksum_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_size (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_membuf__create (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_membuf_t *
checksum_as_key(svn_checksum_t *checksum,
                apr_pool_t *pool)
{
  svn_membuf_t *result = apr_pcalloc(pool, sizeof(*result));
  apr_size_t size = svn_checksum_size(checksum);

  svn_membuf__create(result, size, pool);
  result->size = size; /* exact length is required! */
  memcpy(result->data, checksum->digest, size);

  return result;
}
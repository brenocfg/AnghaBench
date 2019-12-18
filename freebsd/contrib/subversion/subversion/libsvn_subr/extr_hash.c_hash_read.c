#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_3__ {int /*<<< orphan*/  keylen; int /*<<< orphan*/ * key; int /*<<< orphan*/  vallen; scalar_t__ val; } ;
typedef  TYPE_1__ svn_hash__entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_pstrmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash__read_entry (TYPE_1__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_string_ncreate (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
hash_read(apr_hash_t *hash, svn_stream_t *stream, const char *terminator,
          svn_boolean_t incremental, apr_pool_t *pool)
{
  apr_pool_t *iterpool = svn_pool_create(pool);

  while (1)
    {
      svn_hash__entry_t entry;

      svn_pool_clear(iterpool);
      SVN_ERR(svn_hash__read_entry(&entry, stream, terminator,
                                   incremental, iterpool));

      /* end of hash? */
      if (entry.key == NULL)
        break;

      if (entry.val)
        {
          /* Add a new hash entry. */
          apr_hash_set(hash, apr_pstrmemdup(pool, entry.key, entry.keylen),
                       entry.keylen,
                       svn_string_ncreate(entry.val, entry.vallen, pool));
        }
      else
        {
          /* Remove this hash entry. */
          apr_hash_set(hash, entry.key, entry.keylen, NULL);
        }
    }

  svn_pool_destroy(iterpool);
  return SVN_NO_ERROR;
}
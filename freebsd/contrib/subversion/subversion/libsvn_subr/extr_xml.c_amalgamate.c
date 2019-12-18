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
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_hash_get (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  apr_pstrndup (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void
amalgamate(const char **atts,
           apr_hash_t *ht,
           svn_boolean_t preserve,
           apr_pool_t *pool)
{
  const char *key;

  if (atts)
    for (key = *atts; key; key = *(++atts))
      {
        const char *val = *(++atts);
        size_t keylen;
        assert(key != NULL);
        /* kff todo: should we also insist that val be non-null here?
           Probably. */

        keylen = strlen(key);
        if (preserve && ((apr_hash_get(ht, key, keylen)) != NULL))
          continue;
        else
          apr_hash_set(ht, apr_pstrndup(pool, key, keylen), keylen,
                       val ? apr_pstrdup(pool, val) : NULL);
      }
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ prefix_idx; int* fingerprint; } ;
struct TYPE_7__ {int* fingerprint; } ;
struct TYPE_8__ {TYPE_1__ entry_key; } ;
struct TYPE_10__ {TYPE_3__ prefix; TYPE_2__ combined_key; } ;
typedef  TYPE_4__ svn_membuffer_cache_t ;
typedef  int apr_uint64_t ;
typedef  int apr_ssize_t ;

/* Variables and functions */
 int APR_HASH_KEY_STRING ; 
 int APR_UINT64_C (int) ; 
 scalar_t__ NO_INDEX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  combine_long_key (TYPE_4__*,void const*,int) ; 
 int /*<<< orphan*/  memcpy (int*,void const*,int) ; 

__attribute__((used)) static void
combine_key(svn_membuffer_cache_t *cache,
            const void *key,
            apr_ssize_t key_len)
{
  /* copy of *key, padded with 0 */
  apr_uint64_t data[2];

  /* Do we have to compare full keys? */
  if (cache->prefix.prefix_idx == NO_INDEX)
    {
      combine_long_key(cache, key, key_len);
      return;
    }

  /* short, fixed-size keys are the most common case */
  if (key_len == 16)
    {
      memcpy(data, key, 16);
    }
  else if (key_len == 8)
    {
      memcpy(data, key, 8);
      data[1] = 0;
    }
  else
    {
      assert(key_len != APR_HASH_KEY_STRING && key_len < 16);
      data[0] = 0;
      data[1] = 0;
      memcpy(data, key, key_len);
    }

  /* Scramble key DATA to spread the key space more evenly across the
   * cache segments and entry buckets.  All of this shall be reversible
   * to prevent key collisions.  So, we limit ourselves to xor and
   * permutations.
   *
   * Since the entry key must preserve the full key (prefix and KEY),
   * the scramble must not introduce KEY collisions.
   */
  data[1] = (data[1] << 27) | (data[1] >> 37);
  data[1] ^= data[0] & 0xffff;
  data[0] ^= data[1] & APR_UINT64_C(0xffffffffffff0000);

  /* Combine with this cache's prefix.  This is reversible because the
   * prefix is known through to the respective entry_key element.  So,
   * knowing entry_key.prefix_id, we can still reconstruct KEY (and the
   * prefix key).
   */
  cache->combined_key.entry_key.fingerprint[0]
    = data[0] ^ cache->prefix.fingerprint[0];
  cache->combined_key.entry_key.fingerprint[1]
    = data[1] ^ cache->prefix.fingerprint[1];
}
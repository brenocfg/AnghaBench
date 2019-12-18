#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
struct TYPE_8__ {int size; int shift; scalar_t__* offsets; int /*<<< orphan*/ * last_matches; int /*<<< orphan*/ * prefixes; scalar_t__ used; int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ hash_t ;
typedef  int /*<<< orphan*/  hash_key_t ;
typedef  scalar_t__ apr_uint32_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 scalar_t__ NO_OFFSET ; 
 int /*<<< orphan*/  allocate_hash_members (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_key (scalar_t__) ; 
 size_t hash_to_index (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
grow_hash(hash_t *hash,
          svn_stringbuf_t *text,
          apr_size_t min_size)
{
  hash_t copy;
  apr_size_t i;

  /* determine the new hash size */
  apr_size_t new_size = hash->size * 2;
  apr_size_t new_shift = hash->shift - 1;
  while (new_size < min_size)
    {
      new_size *= 2;
      --new_shift;
    }

  /* allocate new hash */
  allocate_hash_members(&copy, new_size, hash->pool);
  copy.used = 0;
  copy.shift = new_shift;

  /* copy / translate data */
  for (i = 0; i < hash->size; ++i)
    {
      apr_uint32_t offset = hash->offsets[i];
      if (offset != NO_OFFSET)
        {
          hash_key_t key = hash_key(text->data + offset);
          size_t idx = hash_to_index(&copy, key);

          if (copy.offsets[idx] == NO_OFFSET)
            copy.used++;

          copy.prefixes[idx] = hash->prefixes[i];
          copy.offsets[idx] = offset;
          copy.last_matches[idx] = hash->last_matches[i];
        }
    }

  *hash = copy;
}
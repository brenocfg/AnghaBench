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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 size_t TEST_CHUNK_SIZE ; 
 int /*<<< orphan*/  TEST_INIT () ; 
 size_t TEST_MAX_SUB_ITERS ; 
 int /*<<< orphan*/ * data ; 
 int /*<<< orphan*/  jmem_finalize () ; 
 int /*<<< orphan*/  jmem_heap_stats_print () ; 
 int /*<<< orphan*/  jmem_init () ; 
 scalar_t__ jmem_pools_alloc (size_t) ; 
 int /*<<< orphan*/  jmem_pools_collect_empty () ; 
 int /*<<< orphan*/  jmem_pools_free (scalar_t__*,size_t) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,size_t) ; 
 scalar_t__** ptrs ; 
 int rand () ; 
 scalar_t__ test_iters ; 

int
main (void)
{
  TEST_INIT ();

  jmem_init ();

  for (uint32_t i = 0; i < test_iters; i++)
  {
    const size_t subiters = ((size_t) rand () % TEST_MAX_SUB_ITERS) + 1;

    for (size_t j = 0; j < subiters; j++)
    {
      ptrs[j] = (uint8_t *) jmem_pools_alloc (TEST_CHUNK_SIZE);

      if (ptrs[j] != NULL)
      {
        for (size_t k = 0; k < TEST_CHUNK_SIZE; k++)
        {
          ptrs[j][k] = (uint8_t) (rand () % 256);
        }

        memcpy (data[j], ptrs[j], TEST_CHUNK_SIZE);
      }
    }

    /* jmem_heap_print (false); */

    for (size_t j = 0; j < subiters; j++)
    {
      if (rand () % 256 == 0)
      {
        jmem_pools_collect_empty ();
      }

      if (ptrs[j] != NULL)
      {
        TEST_ASSERT (!memcmp (data[j], ptrs[j], TEST_CHUNK_SIZE));

        jmem_pools_free (ptrs[j], TEST_CHUNK_SIZE);
      }
    }
  }

#ifdef JMEM_STATS
  jmem_heap_stats_print ();
#endif /* JMEM_STATS */

  jmem_finalize ();

  return 0;
}
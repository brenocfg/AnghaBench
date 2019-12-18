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
typedef  size_t uint8_t ;

/* Variables and functions */
 size_t BASIC_SIZE ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_INIT () ; 
 int /*<<< orphan*/  ecma_finalize () ; 
 int /*<<< orphan*/  ecma_init () ; 
 int /*<<< orphan*/  jmem_finalize () ; 
 scalar_t__ jmem_heap_alloc_block (size_t) ; 
 int /*<<< orphan*/  jmem_heap_free_block (size_t*,size_t) ; 
 size_t* jmem_heap_realloc_block (size_t*,size_t,size_t) ; 
 int /*<<< orphan*/  jmem_init () ; 

int
main (void)
{
  TEST_INIT ();

  jmem_init ();
  ecma_init ();

  {
    uint8_t *block1_p = (uint8_t *) jmem_heap_alloc_block (BASIC_SIZE);
    uint8_t *block2_p = (uint8_t *) jmem_heap_alloc_block (BASIC_SIZE);
    uint8_t *block3_p = (uint8_t *) jmem_heap_alloc_block (BASIC_SIZE);

    /* [block1 64] [block2 64] [block3 64] [...] */

    for (uint8_t i = 0; i < BASIC_SIZE; i++)
    {
      block2_p[i] = i;
    }

    /* Realloc by moving */
    block2_p = jmem_heap_realloc_block (block2_p, BASIC_SIZE, BASIC_SIZE * 2);

    /* [block1 64] [free 64] [block3 64] [block2 128] [...] */

    for (uint8_t i = 0; i < BASIC_SIZE; i++)
    {
      TEST_ASSERT (block2_p[i] == i);
    }

    for (uint8_t i = BASIC_SIZE; i < BASIC_SIZE * 2; i++)
    {
      block2_p[i] = i;
    }

    uint8_t *block4_p = (uint8_t *) jmem_heap_alloc_block (BASIC_SIZE * 2);

    /* [block1 64] [free 64] [block3 64] [block2 128] [block4 128] [...] */

    jmem_heap_free_block (block3_p, BASIC_SIZE);

    /* [block1 64] [free 128] [block2 128] [block4 128] [...] */

    /* Realloc by extending front */
    block2_p = (uint8_t *) jmem_heap_realloc_block (block2_p, BASIC_SIZE * 2, BASIC_SIZE * 3);

    /* [block1 64] [free 64] [block2 192] [block4 128] [...] */

    for (uint8_t i = 0; i < BASIC_SIZE * 2; i++)
    {
      TEST_ASSERT (block2_p[i] == i);
    }

    /* Shrink */
    block2_p = (uint8_t *) jmem_heap_realloc_block (block2_p, BASIC_SIZE * 3, BASIC_SIZE);

    /* [block1 64] [free 64] [block2 64] [free 128] [block4 128] [...] */

    for (uint8_t i = 0; i < BASIC_SIZE; i++)
    {
      TEST_ASSERT (block2_p[i] == i);
    }

    for (uint8_t i = 0; i < BASIC_SIZE; i++)
    {
      block1_p[i] = i;
    }

    /* Grow in place */
    block1_p = (uint8_t *) jmem_heap_realloc_block (block1_p, BASIC_SIZE, BASIC_SIZE * 2);

    /* [block1 128] [block2 64] [free 128] [block4 128] [...] */

    for (uint8_t i = 0; i < BASIC_SIZE; i++)
    {
      TEST_ASSERT (block1_p[i] == i);
    }

    jmem_heap_free_block (block1_p, BASIC_SIZE * 2);
    jmem_heap_free_block (block2_p, BASIC_SIZE);
    jmem_heap_free_block (block4_p, BASIC_SIZE * 2);
  }

  ecma_finalize ();
  jmem_finalize ();

  return 0;
}
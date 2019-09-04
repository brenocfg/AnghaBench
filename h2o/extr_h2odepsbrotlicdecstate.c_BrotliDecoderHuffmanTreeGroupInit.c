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
typedef  int uint32_t ;
typedef  void* uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/ * codes; int /*<<< orphan*/ ** htrees; void* num_htrees; void* alphabet_size; } ;
typedef  TYPE_1__ HuffmanTreeGroup ;
typedef  int /*<<< orphan*/  HuffmanCode ;
typedef  int /*<<< orphan*/  BrotliDecoderState ;
typedef  int BROTLI_BOOL ;

/* Variables and functions */
 scalar_t__ BROTLI_ALLOC (int /*<<< orphan*/ *,size_t const) ; 
 size_t* kMaxHuffmanTableSize ; 

BROTLI_BOOL BrotliDecoderHuffmanTreeGroupInit(BrotliDecoderState* s,
    HuffmanTreeGroup* group, uint32_t alphabet_size, uint32_t ntrees) {
  /* Pack two allocations into one */
  const size_t max_table_size = kMaxHuffmanTableSize[(alphabet_size + 31) >> 5];
  const size_t code_size = sizeof(HuffmanCode) * ntrees * max_table_size;
  const size_t htree_size = sizeof(HuffmanCode*) * ntrees;
  /* Pointer alignment is, hopefully, wider than sizeof(HuffmanCode). */
  HuffmanCode** p = (HuffmanCode**)BROTLI_ALLOC(s, code_size + htree_size);
  group->alphabet_size = (uint16_t)alphabet_size;
  group->num_htrees = (uint16_t)ntrees;
  group->htrees = p;
  group->codes = (HuffmanCode*)(&p[ntrees]);
  return !!p;
}
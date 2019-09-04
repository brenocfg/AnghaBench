#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  lgwin; } ;
typedef  int /*<<< orphan*/  MemoryManager ;
typedef  int /*<<< orphan*/  HasherHandle ;
typedef  int /*<<< orphan*/  Command ;
typedef  TYPE_1__ BrotliEncoderParams ;
typedef  int /*<<< orphan*/  BrotliDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  BROTLI_ALLOC (int /*<<< orphan*/ *,int,size_t) ; 
 int /*<<< orphan*/  BROTLI_FREE (int /*<<< orphan*/ *,int) ; 
 scalar_t__ BROTLI_IS_OOM (int /*<<< orphan*/ *) ; 
 size_t BROTLI_MAX_BACKWARD_LIMIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BrotliInitZopfliNodes (int,size_t) ; 
 scalar_t__ BrotliZopfliComputeShortestPath (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,size_t,int /*<<< orphan*/  const*,size_t,TYPE_1__ const*,size_t const,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BrotliZopfliCreateCommands (size_t,size_t,size_t const,int,int*,size_t*,TYPE_1__ const*,int /*<<< orphan*/ *,size_t*) ; 
 int ZopfliNode ; 
 int nodes ; 

void BrotliCreateZopfliBackwardReferences(
    MemoryManager* m, const BrotliDictionary* dictionary, size_t num_bytes,
    size_t position, const uint8_t* ringbuffer, size_t ringbuffer_mask,
    const BrotliEncoderParams* params, HasherHandle hasher, int* dist_cache,
    size_t* last_insert_len, Command* commands, size_t* num_commands,
    size_t* num_literals) {
  const size_t max_backward_limit = BROTLI_MAX_BACKWARD_LIMIT(params->lgwin);
  ZopfliNode* nodes;
  nodes = BROTLI_ALLOC(m, ZopfliNode, num_bytes + 1);
  if (BROTLI_IS_OOM(m)) return;
  BrotliInitZopfliNodes(nodes, num_bytes + 1);
  *num_commands += BrotliZopfliComputeShortestPath(m, dictionary, num_bytes,
      position, ringbuffer, ringbuffer_mask, params, max_backward_limit,
      dist_cache, hasher, nodes);
  if (BROTLI_IS_OOM(m)) return;
  BrotliZopfliCreateCommands(num_bytes, position, max_backward_limit, nodes,
      dist_cache, last_insert_len, params, commands, num_literals);
  BROTLI_FREE(m, nodes);
}
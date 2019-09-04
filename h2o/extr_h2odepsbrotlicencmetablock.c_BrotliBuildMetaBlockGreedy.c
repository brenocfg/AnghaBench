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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  MetaBlockSplit ;
typedef  int /*<<< orphan*/  MemoryManager ;
typedef  int /*<<< orphan*/  ContextType ;
typedef  int /*<<< orphan*/  Command ;

/* Variables and functions */
 int /*<<< orphan*/  BrotliBuildMetaBlockGreedyInternal (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 

void BrotliBuildMetaBlockGreedy(MemoryManager* m,
                                const uint8_t* ringbuffer,
                                size_t pos,
                                size_t mask,
                                uint8_t prev_byte,
                                uint8_t prev_byte2,
                                ContextType literal_context_mode,
                                size_t num_contexts,
                                const uint32_t* static_context_map,
                                const Command* commands,
                                size_t n_commands,
                                MetaBlockSplit* mb) {
  if (num_contexts == 1) {
    BrotliBuildMetaBlockGreedyInternal(m, ringbuffer, pos, mask, prev_byte,
        prev_byte2, literal_context_mode, 1, NULL, commands, n_commands, mb);
  } else {
    BrotliBuildMetaBlockGreedyInternal(m, ringbuffer, pos, mask, prev_byte,
        prev_byte2, literal_context_mode, num_contexts, static_context_map,
        commands, n_commands, mb);
  }
}
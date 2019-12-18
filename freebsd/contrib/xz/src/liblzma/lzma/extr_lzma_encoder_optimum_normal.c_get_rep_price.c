#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  lzma_lzma_state ;
struct TYPE_4__ {int /*<<< orphan*/  rep_len_encoder; } ;
typedef  TYPE_1__ lzma_lzma1_encoder ;

/* Variables and functions */
 scalar_t__ get_len_price (int /*<<< orphan*/ *,scalar_t__ const,scalar_t__ const) ; 
 scalar_t__ get_pure_rep_price (TYPE_1__ const* const,scalar_t__ const,int /*<<< orphan*/  const,scalar_t__ const) ; 

__attribute__((used)) static inline uint32_t
get_rep_price(const lzma_lzma1_encoder *const coder, const uint32_t rep_index,
		const uint32_t len, const lzma_lzma_state state,
		const uint32_t pos_state)
{
	return get_len_price(&coder->rep_len_encoder, len, pos_state)
		+ get_pure_rep_price(coder, rep_index, state, pos_state);
}
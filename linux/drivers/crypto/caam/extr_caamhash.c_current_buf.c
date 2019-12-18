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
typedef  int /*<<< orphan*/  u8 ;
struct caam_hash_state {int /*<<< orphan*/ * buf_0; int /*<<< orphan*/ * buf_1; scalar_t__ current_buf; } ;

/* Variables and functions */

__attribute__((used)) static inline u8 *current_buf(struct caam_hash_state *state)
{
	return state->current_buf ? state->buf_1 : state->buf_0;
}
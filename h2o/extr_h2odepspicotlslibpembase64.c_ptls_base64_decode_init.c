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
struct TYPE_3__ {int nbo; int /*<<< orphan*/  status; scalar_t__ v; scalar_t__ nbc; } ;
typedef  TYPE_1__ ptls_base64_decode_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTLS_BASE64_DECODE_IN_PROGRESS ; 

void ptls_base64_decode_init(ptls_base64_decode_state_t *state)
{
    state->nbc = 0;
    state->nbo = 3;
    state->v = 0;
    state->status = PTLS_BASE64_DECODE_IN_PROGRESS;
}
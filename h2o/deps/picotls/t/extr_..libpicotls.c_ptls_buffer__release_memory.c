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
struct TYPE_3__ {int /*<<< orphan*/  base; scalar_t__ is_allocated; int /*<<< orphan*/  off; } ;
typedef  TYPE_1__ ptls_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptls_clear_memory (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ptls_buffer__release_memory(ptls_buffer_t *buf)
{
    ptls_clear_memory(buf->base, buf->off);
    if (buf->is_allocated)
        free(buf->base);
}
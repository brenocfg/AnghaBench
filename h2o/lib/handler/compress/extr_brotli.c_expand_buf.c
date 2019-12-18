#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ size; scalar_t__ entries; } ;
struct st_brotli_context_t {int /*<<< orphan*/  buf_capacity; TYPE_1__ bufs; } ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_mem_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_sendvec_init_raw (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_vector_reserve (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void expand_buf(struct st_brotli_context_t *self)
{
    h2o_vector_reserve(NULL, &self->bufs, self->bufs.size + 1);
    h2o_sendvec_init_raw(self->bufs.entries + self->bufs.size++, h2o_mem_alloc(self->buf_capacity), 0);
}
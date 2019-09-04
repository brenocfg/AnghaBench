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
struct TYPE_4__ {scalar_t__ size; int /*<<< orphan*/ * entries; } ;
typedef  TYPE_1__ iovec_vector_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_SIZE ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mem_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_vector_reserve (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void expand_buf(iovec_vector_t *bufs)
{
    h2o_vector_reserve(NULL, bufs, bufs->size + 1);
    bufs->entries[bufs->size++] = h2o_iovec_init(h2o_mem_alloc(BUF_SIZE), 0);
}
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
typedef  int /*<<< orphan*/  h2o_mem_pool_t ;
struct TYPE_4__ {scalar_t__ size; int /*<<< orphan*/ * entries; } ;
typedef  TYPE_1__ h2o_headers_t ;
typedef  int /*<<< orphan*/  h2o_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_vector_reserve (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void add_header(h2o_mem_pool_t *pool, h2o_headers_t *headers, const h2o_header_t *header)
{
    h2o_vector_reserve(pool, headers, headers->size + 1);
    headers->entries[headers->size++] = *header;
}
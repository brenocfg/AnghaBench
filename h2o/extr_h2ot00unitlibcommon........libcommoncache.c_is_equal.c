#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ len; int /*<<< orphan*/  base; } ;
struct TYPE_6__ {TYPE_1__ key; } ;
typedef  TYPE_2__ h2o_cache_ref_t ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int is_equal(h2o_cache_ref_t *x, h2o_cache_ref_t *y)
{
    return x->key.len == y->key.len && memcmp(x->key.base, y->key.base, x->key.len) == 0;
}
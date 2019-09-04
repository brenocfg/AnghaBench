#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* name; } ;
typedef  TYPE_2__ h2o_header_t ;
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int headers_sort_cb(const void *_x, const void *_y)
{
    const h2o_header_t *x = _x, *y = _y;

    if (x->name->len < y->name->len)
        return -1;
    if (x->name->len > y->name->len)
        return 1;
    return memcmp(x->name->base, y->name->base, x->name->len);
}
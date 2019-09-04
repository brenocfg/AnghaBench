#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  len; } ;
struct TYPE_7__ {TYPE_2__ value; TYPE_1__* name; } ;
typedef  TYPE_3__ h2o_header_t ;
struct TYPE_5__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 scalar_t__ calc_capacity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t calc_headers_capacity(const h2o_header_t *headers, size_t num_headers)
{
    const h2o_header_t *header;
    size_t capacity = 0;
    for (header = headers; num_headers != 0; ++header, --num_headers)
        capacity += calc_capacity(header->name->len, header->value.len);
    return capacity;
}
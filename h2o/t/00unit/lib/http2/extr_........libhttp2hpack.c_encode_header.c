#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  h2o_hpack_header_table_t ;
struct TYPE_4__ {int /*<<< orphan*/  dont_compress; } ;
struct TYPE_5__ {TYPE_1__ flags; int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ h2o_header_t ;

/* Variables and functions */
 int /*<<< orphan*/ * do_encode_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t *encode_header(h2o_hpack_header_table_t *header_table, uint8_t *dst, const h2o_header_t *header)
{
    return do_encode_header(header_table, dst, header->name, &header->value, header->flags.dont_compress);
}
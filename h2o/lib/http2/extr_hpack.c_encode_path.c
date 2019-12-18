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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ h2o_iovec_t ;
typedef  int /*<<< orphan*/  h2o_hpack_header_table_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  H2O_TOKEN_PATH ; 
 int /*<<< orphan*/ * encode_header_token (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ h2o_memis (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t *encode_path(h2o_hpack_header_table_t *header_table, uint8_t *dst, h2o_iovec_t value)
{
    if (h2o_memis(value.base, value.len, H2O_STRLIT("/"))) {
        *dst++ = 0x84;
        return dst;
    }
    if (h2o_memis(value.base, value.len, H2O_STRLIT("/index.html"))) {
        *dst++ = 0x85;
        return dst;
    }
    return encode_header_token(header_table, dst, H2O_TOKEN_PATH, &value);
}
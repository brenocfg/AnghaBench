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

/* Variables and functions */
 int /*<<< orphan*/  h2o_hpack_encode_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t *encode_literal_header_without_indexing(uint8_t *dst, const h2o_iovec_t *name, const h2o_iovec_t *value)
{
    /* literal header field without indexing / never indexed */
    *dst++ = 0;
    dst += h2o_hpack_encode_string(dst, name->base, name->len);
    dst += h2o_hpack_encode_string(dst, value->base, value->len);
    return dst;
}
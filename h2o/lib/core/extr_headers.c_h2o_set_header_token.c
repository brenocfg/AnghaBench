#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_10__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ h2o_token_t ;
typedef  int /*<<< orphan*/  h2o_mem_pool_t ;
struct TYPE_11__ {size_t size; TYPE_3__* entries; } ;
typedef  TYPE_2__ h2o_headers_t ;
struct TYPE_13__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_12__ {TYPE_6__ value; int /*<<< orphan*/ * name; } ;
typedef  TYPE_3__ h2o_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int h2o_add_header (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__ const*,int /*<<< orphan*/ *,char const*,size_t) ; 
 TYPE_6__ h2o_concat (int /*<<< orphan*/ *,TYPE_6__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ h2o_contains_token (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,size_t,char) ; 
 int /*<<< orphan*/  h2o_iovec_init (char const*,...) ; 

ssize_t h2o_set_header_token(h2o_mem_pool_t *pool, h2o_headers_t *headers, const h2o_token_t *token, const char *value,
                             size_t value_len)
{
    ssize_t found = -1;
    size_t i;
    for (i = 0; i != headers->size; ++i) {
        if (headers->entries[i].name == &token->buf) {
            if (h2o_contains_token(headers->entries[i].value.base, headers->entries[i].value.len, value, value_len, ','))
                return -1;
            found = i;
        }
    }
    if (found != -1) {
        h2o_header_t *dest = headers->entries + found;
        dest->value = h2o_concat(pool, dest->value, h2o_iovec_init(H2O_STRLIT(", ")), h2o_iovec_init(value, value_len));
        return found;
    } else {
        return h2o_add_header(pool, headers, token, NULL, value, value_len);
    }
}
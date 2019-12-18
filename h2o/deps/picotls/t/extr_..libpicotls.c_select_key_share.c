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
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {scalar_t__ id; } ;
typedef  TYPE_1__ ptls_key_exchange_algorithm_t ;
typedef  int /*<<< orphan*/  ptls_iovec_t ;

/* Variables and functions */
 int PTLS_ALERT_ILLEGAL_PARAMETER ; 
 int decode_key_share_entry (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const* const) ; 

__attribute__((used)) static int select_key_share(ptls_key_exchange_algorithm_t **selected, ptls_iovec_t *peer_key,
                            ptls_key_exchange_algorithm_t **candidates, const uint8_t **src, const uint8_t *const end,
                            int expect_one)
{
    int ret;

    *selected = NULL;

    if (expect_one && *src == end) {
        ret = PTLS_ALERT_ILLEGAL_PARAMETER;
        goto Exit;
    }

    while (*src != end) {
        uint16_t group;
        ptls_iovec_t key;
        if ((ret = decode_key_share_entry(&group, &key, src, end)) != 0)
            goto Exit;
        ptls_key_exchange_algorithm_t **c = candidates;
        for (; *c != NULL; ++c) {
            if (*selected == NULL && (*c)->id == group) {
                *selected = *c;
                *peer_key = key;
            }
        }
        if (expect_one) {
            ret = *selected != NULL ? 0 : PTLS_ALERT_ILLEGAL_PARAMETER;
            goto Exit;
        }
    }

    ret = 0;

Exit:
    return ret;
}
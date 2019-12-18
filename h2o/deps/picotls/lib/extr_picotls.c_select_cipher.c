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
typedef  TYPE_1__ ptls_cipher_suite_t ;

/* Variables and functions */
 int PTLS_ALERT_HANDSHAKE_FAILURE ; 
 int ptls_decode16 (scalar_t__*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const* const) ; 

__attribute__((used)) static int select_cipher(ptls_cipher_suite_t **selected, ptls_cipher_suite_t **candidates, const uint8_t *src,
                         const uint8_t *const end)
{
    int ret;

    while (src != end) {
        uint16_t id;
        if ((ret = ptls_decode16(&id, &src, end)) != 0)
            goto Exit;
        ptls_cipher_suite_t **c = candidates;
        for (; *c != NULL; ++c) {
            if ((*c)->id == id) {
                *selected = *c;
                return 0;
            }
        }
    }

    ret = PTLS_ALERT_HANDSHAKE_FAILURE;

Exit:
    return ret;
}
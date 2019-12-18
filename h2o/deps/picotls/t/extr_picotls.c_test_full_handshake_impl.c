#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  TEST_HANDSHAKE_1RTT ; 
 int /*<<< orphan*/  ok (int) ; 
 int /*<<< orphan*/  ptls_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sc_callcnt ; 
 int /*<<< orphan*/  test_handshake (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void test_full_handshake_impl(int require_client_authentication)
{
    sc_callcnt = 0;

    test_handshake(ptls_iovec_init(NULL, 0), TEST_HANDSHAKE_1RTT, 0, 0, require_client_authentication);
    if (require_client_authentication) {
        ok(sc_callcnt == 2);
    } else {
        ok(sc_callcnt == 1);
    }

    test_handshake(ptls_iovec_init(NULL, 0), TEST_HANDSHAKE_1RTT, 0, 0, require_client_authentication);
    if (require_client_authentication) {
        ok(sc_callcnt == 4);
    } else {
        ok(sc_callcnt == 2);
    }

    test_handshake(ptls_iovec_init(NULL, 0), TEST_HANDSHAKE_1RTT, 0, 1, require_client_authentication);
    if (require_client_authentication) {
        ok(sc_callcnt == 6);
    } else {
        ok(sc_callcnt == 3);
    }
}
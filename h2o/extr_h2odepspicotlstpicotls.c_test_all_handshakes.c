#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ ptls_sign_certificate_t ;
struct TYPE_7__ {TYPE_1__* sign_certificate; } ;

/* Variables and functions */
 TYPE_4__* ctx ; 
 TYPE_4__* ctx_peer ; 
 TYPE_1__* sc_orig ; 
 TYPE_1__* second_sc_orig ; 
 int /*<<< orphan*/  second_sign_certificate ; 
 int /*<<< orphan*/  sign_certificate ; 
 int /*<<< orphan*/  subtest (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_enforce_retry_stateful ; 
 int /*<<< orphan*/  test_enforce_retry_stateless ; 
 int /*<<< orphan*/  test_full_handshake ; 
 int /*<<< orphan*/  test_full_handshake_with_client_authentication ; 
 int /*<<< orphan*/  test_handshake_api ; 
 int /*<<< orphan*/  test_hrr_handshake ; 
 int /*<<< orphan*/  test_hrr_stateless_handshake ; 
 int /*<<< orphan*/  test_key_update ; 
 int /*<<< orphan*/  test_resumption ; 
 int /*<<< orphan*/  test_resumption_different_preferred_key_share ; 
 int /*<<< orphan*/  test_resumption_with_client_authentication ; 
 int /*<<< orphan*/  test_stateless_hrr_aad_change ; 

__attribute__((used)) static void test_all_handshakes(void)
{
    ptls_sign_certificate_t server_sc = {sign_certificate};
    sc_orig = ctx_peer->sign_certificate;
    ctx_peer->sign_certificate = &server_sc;

    ptls_sign_certificate_t client_sc = {second_sign_certificate};
    if (ctx_peer != ctx) {
        second_sc_orig = ctx->sign_certificate;
        ctx->sign_certificate = &client_sc;
    }

    subtest("full-handshake", test_full_handshake);
    subtest("full-handshake-with-client-authentication", test_full_handshake_with_client_authentication);
    subtest("hrr-handshake", test_hrr_handshake);
    subtest("hrr-stateless-handshake", test_hrr_stateless_handshake);
    subtest("resumption", test_resumption);
    subtest("resumption-different-preferred-key-share", test_resumption_different_preferred_key_share);
    subtest("resumption-with-client-authentication", test_resumption_with_client_authentication);

    subtest("enforce-retry-stateful", test_enforce_retry_stateful);
    subtest("enforce-retry-stateless", test_enforce_retry_stateless);

    subtest("stateless-hrr-aad-change", test_stateless_hrr_aad_change);

    subtest("key-update", test_key_update);

    subtest("handshake-api", test_handshake_api);

    ctx_peer->sign_certificate = sc_orig;

    if (ctx_peer != ctx)
        ctx->sign_certificate = second_sc_orig;
}
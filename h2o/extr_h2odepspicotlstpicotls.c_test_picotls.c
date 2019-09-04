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
 int /*<<< orphan*/  subtest (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_aes128ctr ; 
 int /*<<< orphan*/  test_aes128ecb ; 
 int /*<<< orphan*/  test_aes128gcm ; 
 int /*<<< orphan*/  test_aes256ecb ; 
 int /*<<< orphan*/  test_aes256gcm ; 
 int /*<<< orphan*/  test_all_handshakes ; 
 int /*<<< orphan*/  test_base64_decode ; 
 int /*<<< orphan*/  test_chacha20 ; 
 int /*<<< orphan*/  test_chacha20poly1305 ; 
 int /*<<< orphan*/  test_ffx ; 
 int /*<<< orphan*/  test_fragmented_message ; 
 int /*<<< orphan*/  test_hkdf ; 
 int /*<<< orphan*/  test_hmac_sha256 ; 
 int /*<<< orphan*/  test_is_ipaddr ; 
 int /*<<< orphan*/  test_sha256 ; 
 int /*<<< orphan*/  test_sha384 ; 

void test_picotls(void)
{
    subtest("is_ipaddr", test_is_ipaddr);
    subtest("sha256", test_sha256);
    subtest("sha384", test_sha384);
    subtest("hmac-sha256", test_hmac_sha256);
    subtest("hkdf", test_hkdf);
    subtest("aes128gcm", test_aes128gcm);
    subtest("aes256gcm", test_aes256gcm);
    subtest("chacha20poly1305", test_chacha20poly1305);
    subtest("aes128ecb", test_aes128ecb);
    subtest("aes256ecb", test_aes256ecb);
    subtest("aes128ctr", test_aes128ctr);
    subtest("chacha20", test_chacha20);
    subtest("ffx", test_ffx);
    subtest("base64-decode", test_base64_decode);
    subtest("fragmented-message", test_fragmented_message);
    subtest("handshake", test_all_handshakes);
}
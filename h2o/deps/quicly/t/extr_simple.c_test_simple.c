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
 int /*<<< orphan*/  simple_http ; 
 int /*<<< orphan*/  subtest (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_close ; 
 int /*<<< orphan*/  test_handshake ; 
 int /*<<< orphan*/  test_reset_after_close ; 
 int /*<<< orphan*/  test_rst_during_loss ; 
 int /*<<< orphan*/  test_rst_then_close ; 
 int /*<<< orphan*/  test_send_then_close ; 
 int /*<<< orphan*/  tiny_connection_window ; 
 int /*<<< orphan*/  tiny_stream_window ; 

void test_simple(void)
{
    subtest("handshake", test_handshake);
    subtest("simple-http", simple_http);
    subtest("rst-then-close", test_rst_then_close);
    subtest("send-then-close", test_send_then_close);
    subtest("reset-after-close", test_reset_after_close);
    subtest("tiny-stream-window", tiny_stream_window);
    subtest("rst-during-loss", test_rst_during_loss);
    subtest("close", test_close);
    subtest("tiny-connection-window", tiny_connection_window);
}
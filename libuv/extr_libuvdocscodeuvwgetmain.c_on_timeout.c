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
typedef  int /*<<< orphan*/  uv_timer_t ;

/* Variables and functions */
 int /*<<< orphan*/  CURL_SOCKET_TIMEOUT ; 
 int /*<<< orphan*/  check_multi_info () ; 
 int /*<<< orphan*/  curl_handle ; 
 int /*<<< orphan*/  curl_multi_socket_action (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

void on_timeout(uv_timer_t *req) {
    int running_handles;
    curl_multi_socket_action(curl_handle, CURL_SOCKET_TIMEOUT, 0, &running_handles);
    check_multi_info();
}
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
 int /*<<< orphan*/  http_connection_retry_test_basic (void*,char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
http_connection_retry_test_impl(void *arg, int ssl)
{
	http_connection_retry_test_basic(arg, "127.0.0.1", NULL, ssl);
}
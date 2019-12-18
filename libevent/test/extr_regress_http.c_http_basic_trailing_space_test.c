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
 int /*<<< orphan*/  http_basic_test_impl (void*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void http_basic_trailing_space_test(void *arg)
{ http_basic_test_impl(arg, 0, "GET /test HTTP/1.1 "); }
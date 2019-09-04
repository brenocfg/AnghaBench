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
 int done_testing () ; 
 int /*<<< orphan*/  subtest (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_chunked ; 
 int /*<<< orphan*/  test_chunked_consume_trailer ; 
 int /*<<< orphan*/  test_headers ; 
 int /*<<< orphan*/  test_request ; 
 int /*<<< orphan*/  test_response ; 

int main(int argc, char **argv)
{
    subtest("request", test_request);
    subtest("response", test_response);
    subtest("headers", test_headers);
    subtest("chunked", test_chunked);
    subtest("chunked-consume-trailer", test_chunked_consume_trailer);
    return done_testing();
}
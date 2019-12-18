#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int off; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ ptls_buffer_t ;
typedef  int /*<<< orphan*/  ptls_base64_decode_state_t ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ok (int) ; 
 int ptls_base64_decode (char*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ptls_base64_decode_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptls_buffer_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  ptls_buffer_init (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_base64_decode(void)
{
    ptls_base64_decode_state_t state;
    ptls_buffer_t buf;
    int ret;

    ptls_buffer_init(&buf, "", 0);

    ptls_base64_decode_init(&state);
    ret = ptls_base64_decode("aGVsbG8gd29ybGQ=", &state, &buf);
    ok(ret == 0);
    ok(buf.off == 11);
    ok(memcmp(buf.base, "hello world", 11) == 0);

    buf.off = 0;

    ptls_base64_decode_init(&state);
    ret = ptls_base64_decode("a$b", &state, &buf);
    ok(ret != 0);

    buf.off = 0;

    ptls_base64_decode_init(&state);
    ret = ptls_base64_decode("a\xFF"
                             "b",
                             &state, &buf);
    ok(ret != 0);

    ptls_buffer_dispose(&buf);
}
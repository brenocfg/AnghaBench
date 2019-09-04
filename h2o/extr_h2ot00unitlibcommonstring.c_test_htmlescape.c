#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_mem_pool_t ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 TYPE_1__ h2o_htmlescape (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mem_clear_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mem_init_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_memis (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_htmlescape(void)
{
    h2o_mem_pool_t pool;
    h2o_mem_init_pool(&pool);

#define TEST(src, expected)                                                                                                        \
    do {                                                                                                                           \
        h2o_iovec_t escaped = h2o_htmlescape(&pool, H2O_STRLIT(src));                                                              \
        ok(h2o_memis(escaped.base, escaped.len, H2O_STRLIT(expected)));                                                            \
    } while (0)

    TEST("hello world", "hello world");
    TEST("x < y", "x &lt; y");
    TEST("\0\"&'<>", "\0&quot;&amp;&#39;&lt;&gt;");

#undef TEST

    h2o_mem_clear_pool(&pool);
}
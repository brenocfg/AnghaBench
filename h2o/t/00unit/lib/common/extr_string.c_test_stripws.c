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
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  h2o_memis (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ h2o_str_stripws (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_stripws(void)
{
    h2o_iovec_t t;

    t = h2o_str_stripws(H2O_STRLIT(""));
    ok(h2o_memis(t.base, t.len, H2O_STRLIT("")));
    t = h2o_str_stripws(H2O_STRLIT("hello world"));
    ok(h2o_memis(t.base, t.len, H2O_STRLIT("hello world")));
    t = h2o_str_stripws(H2O_STRLIT("   hello world"));
    ok(h2o_memis(t.base, t.len, H2O_STRLIT("hello world")));
    t = h2o_str_stripws(H2O_STRLIT("hello world   "));
    ok(h2o_memis(t.base, t.len, H2O_STRLIT("hello world")));
    t = h2o_str_stripws(H2O_STRLIT("   hello world   "));
    ok(h2o_memis(t.base, t.len, H2O_STRLIT("hello world")));
    t = h2o_str_stripws(H2O_STRLIT("     "));
    ok(h2o_memis(t.base, t.len, H2O_STRLIT("")));
}
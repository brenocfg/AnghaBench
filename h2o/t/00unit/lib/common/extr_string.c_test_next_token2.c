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
struct TYPE_5__ {char const* base; size_t len; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  NEXT () ; 
 TYPE_1__ h2o_iovec_init (int /*<<< orphan*/ ) ; 
 int h2o_memis (char const*,size_t,int /*<<< orphan*/ ) ; 
 char* h2o_next_token (TYPE_1__*,char,size_t*,TYPE_1__*) ; 
 int /*<<< orphan*/  ok (int) ; 

__attribute__((used)) static void test_next_token2(void)
{
    h2o_iovec_t iter, value;
    const char *name;
    size_t name_len;

#define NEXT()                                                                                                                     \
    if ((name = h2o_next_token(&iter, ',', &name_len, &value)) == NULL) {                                                          \
        ok(0);                                                                                                                     \
        return;                                                                                                                    \
    }

    iter = h2o_iovec_init(H2O_STRLIT("public, max-age=86400, must-revalidate"));
    NEXT();
    ok(h2o_memis(name, name_len, H2O_STRLIT("public")));
    ok(value.base == NULL);
    ok(value.len == 0);
    NEXT();
    ok(h2o_memis(name, name_len, H2O_STRLIT("max-age")));
    ok(h2o_memis(value.base, value.len, H2O_STRLIT("86400")));
    NEXT();
    ok(h2o_memis(name, name_len, H2O_STRLIT("must-revalidate")));
    ok(value.base == NULL);
    ok(value.len == 0);
    name = h2o_next_token(&iter, ',', &name_len, &value);
    ok(name == NULL);

    iter = h2o_iovec_init(H2O_STRLIT("public, max-age = 86400 = c , must-revalidate="));
    NEXT();
    ok(h2o_memis(name, name_len, H2O_STRLIT("public")));
    ok(value.base == NULL);
    ok(value.len == 0);
    NEXT();
    ok(h2o_memis(name, name_len, H2O_STRLIT("max-age")));
    ok(h2o_memis(value.base, value.len, H2O_STRLIT("86400 = c")));
    NEXT();
    ok(h2o_memis(name, name_len, H2O_STRLIT("must-revalidate")));
    name = h2o_next_token(&iter, ',', &name_len, &value);
    ok(h2o_memis(value.base, value.len, H2O_STRLIT("")));

#undef NEXT
}
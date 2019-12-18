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
typedef  int /*<<< orphan*/  h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  NEXT () ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ ) ; 
 int h2o_memis (char const*,size_t,int /*<<< orphan*/ ) ; 
 char* h2o_next_token (int /*<<< orphan*/ *,char,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int) ; 

__attribute__((used)) static void test_next_token(void)
{
    h2o_iovec_t iter;
    const char *token;
    size_t token_len;

#define NEXT()                                                                                                                     \
    if ((token = h2o_next_token(&iter, ',', &token_len, NULL)) == NULL) {                                                          \
        ok(0);                                                                                                                     \
        return;                                                                                                                    \
    }

    iter = h2o_iovec_init(H2O_STRLIT("public, max-age=86400, must-revalidate"));
    NEXT();
    ok(h2o_memis(token, token_len, H2O_STRLIT("public")));
    NEXT();
    ok(h2o_memis(token, token_len, H2O_STRLIT("max-age=86400")));
    NEXT();
    ok(h2o_memis(token, token_len, H2O_STRLIT("must-revalidate")));
    token = h2o_next_token(&iter, ',', &token_len, NULL);
    ok(token == NULL);

    iter = h2o_iovec_init(H2O_STRLIT("  public  ,max-age=86400  ,"));
    NEXT();
    ok(h2o_memis(token, token_len, H2O_STRLIT("public")));
    NEXT();
    ok(h2o_memis(token, token_len, H2O_STRLIT("max-age=86400")));
    token = h2o_next_token(&iter, ',', &token_len, NULL);
    ok(token == NULL);

    iter = h2o_iovec_init(H2O_STRLIT(""));
    token = h2o_next_token(&iter, ',', &token_len, NULL);
    ok(token == NULL);

    iter = h2o_iovec_init(H2O_STRLIT(", ,a, "));
    NEXT();
    ok(token_len == 0);
    NEXT();
    ok(token_len == 0);
    NEXT();
    ok(h2o_memis(token, token_len, H2O_STRLIT("a")));
    token = h2o_next_token(&iter, ',', &token_len, NULL);
    ok(token == NULL);

#undef NEXT
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct expected_t {char* member_0; int member_1; int /*<<< orphan*/ * path; } ;
typedef  int /*<<< orphan*/  h2o_mem_pool_t ;
struct TYPE_7__ {char* base; int /*<<< orphan*/  len; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  H2O_URL_SCHEME_HTTP ; 
 int /*<<< orphan*/  H2O_URL_SCHEME_HTTPS ; 
 int /*<<< orphan*/  check_path ; 
 int /*<<< orphan*/  h2o_extract_push_path_from_link_header (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ *,TYPE_1__,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,struct expected_t**,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__ h2o_iovec_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mem_clear_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mem_init_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_memis (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void test_extract_push_path_from_link_header(void)
{
    h2o_mem_pool_t pool;
    h2o_iovec_t base_path = {H2O_STRLIT("/basepath/")}, input_authority = {H2O_STRLIT("basehost")},
                other_authority = {H2O_STRLIT("otherhost")};
    h2o_mem_init_pool(&pool);

#define DO_CHECK(_base_scheme, _base_authority, _input, _filtered_expected, ...)                                                   \
    do {                                                                                                                           \
        h2o_iovec_t input = h2o_iovec_init(_input, strlen(_input)), filtered;                                                      \
        struct expected_t expected[] = {__VA_ARGS__, {NULL}}, *e = expected;                                                       \
        h2o_extract_push_path_from_link_header(&pool, input.base, input.len, base_path, &H2O_URL_SCHEME_HTTP, input_authority,     \
                                               _base_scheme, _base_authority, check_path, &e, &filtered, 0);                       \
        ok(e->path == NULL);                                                                                                       \
        if (_filtered_expected != NULL) {                                                                                          \
            ok(h2o_memis(filtered.base, filtered.len, _filtered_expected, strlen(_filtered_expected)));                            \
        } else {                                                                                                                   \
            ok(h2o_memis(filtered.base, filtered.len, input.base, input.len));                                                     \
        }                                                                                                                          \
    } while (0)

    // basic tests
    DO_CHECK(NULL, NULL, "<http://basehost/otherpath>; rel=preload", NULL, {"/otherpath"});
    DO_CHECK(NULL, NULL, "</otherpath>; rel=preload", NULL, {"/otherpath"});
    DO_CHECK(NULL, NULL, "<otherpath>; rel=preload", NULL, {"/basepath/otherpath"});
    DO_CHECK(NULL, NULL, "<../otherpath>; rel=preload", NULL, {"/otherpath"});
    DO_CHECK(NULL, NULL, "<http:otherpath>; rel=preload", NULL, {"/basepath/otherpath"});

    // negative filters
    DO_CHECK(NULL, NULL, "<../otherpath>; rel=author", NULL, {NULL});
    DO_CHECK(NULL, NULL, "<http://basehost:81/otherpath>; rel=preload", NULL, {NULL});
    DO_CHECK(NULL, NULL, "<https://basehost/otherpath>; rel=preload", NULL, {NULL});
    DO_CHECK(NULL, NULL, "<https:otherpath>; rel=preload", NULL, {NULL});

    // scheme and authority
    DO_CHECK(&H2O_URL_SCHEME_HTTPS, &input_authority, "</otherpath>; rel=preload", NULL, {NULL});
    DO_CHECK(&H2O_URL_SCHEME_HTTP, &input_authority, "</otherpath>; rel=preload", NULL, {"/otherpath"});
    DO_CHECK(&H2O_URL_SCHEME_HTTP, &other_authority, "<http://basehost/otherpath>; rel=preload", NULL, {"/otherpath"});

    // attributes
    DO_CHECK(NULL, NULL, "<http:otherpath>; rel=preload; nopush", NULL, {NULL});
    DO_CHECK(NULL, NULL, "<http:otherpath>; rel=preload; x-http2-push-only", "", {"/basepath/otherpath"});
    DO_CHECK(NULL, NULL, "<http:otherpath>; rel=preload; critical", NULL, {"/basepath/otherpath", 1});

    // multiple entries
    DO_CHECK(&H2O_URL_SCHEME_HTTP, &input_authority, "</firstpath>; rel=preload, </secondpath>; rel=preload", NULL, {"/firstpath"},
             {"/secondpath"});
    DO_CHECK(&H2O_URL_SCHEME_HTTP, &input_authority, "</firstpath>; rel=preload; nopush, </secondpath>; rel=preload", NULL,
             {"/secondpath"});
    DO_CHECK(&H2O_URL_SCHEME_HTTP, &input_authority,
             "</firstpath>; rel=preload; nopush, </secondpath>; nopush; rel=preload; </thirdpath>", NULL, {NULL});
    DO_CHECK(&H2O_URL_SCHEME_HTTP, &input_authority, "</firstpath>; rel=preload; nopush, <secondpath>; rel=notpreload", NULL,
             {NULL});
    DO_CHECK(&H2O_URL_SCHEME_HTTP, &input_authority,
             "</firstpath>; rel=preload, </secondpath>; rel=preload; nopush, </thirdpath>; rel=preload", NULL, {"/firstpath"},
             {"/thirdpath"});
    DO_CHECK(&H2O_URL_SCHEME_HTTP, &input_authority, "hogefoo", NULL, {NULL});
    DO_CHECK(&H2O_URL_SCHEME_HTTP, &input_authority,
             "</111>; rel=preload, </222>; rel=preload; nopush, </333>; rel=preload; x-http2-push-only, </444>; rel=preload",
             "</111>; rel=preload, </222>; rel=preload; nopush, </444>; rel=preload", {"/111"}, {"/333"}, {"/444"});

    h2o_mem_clear_pool(&pool);

#undef DO_CHECK
}
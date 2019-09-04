#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_mem_pool_t ;
struct TYPE_4__ {int len; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 size_t SIZE_MAX ; 
 TYPE_1__ h2o_iovec_init (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  h2o_mem_clear_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mem_init_pool (int /*<<< orphan*/ *) ; 
 TYPE_1__ h2o_url_normalize_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,size_t*,size_t**) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int) ; 

__attribute__((used)) static void test_normalize_path(void)
{
    h2o_mem_pool_t pool;

    h2o_mem_init_pool(&pool);

    size_t q;
    size_t *norm_indexes = NULL;
    h2o_iovec_t input;
    h2o_iovec_t b;

    input = h2o_iovec_init(NULL, 0);
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 1);
    ok(memcmp(b.base, H2O_STRLIT("/")) == 0);
    ok(q == SIZE_MAX);
    ok(norm_indexes == NULL);

    input = h2o_iovec_init(H2O_STRLIT("a"));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 2);
    ok(memcmp(b.base, H2O_STRLIT("/a")) == 0);
    ok(q == SIZE_MAX);
    ok(norm_indexes != NULL);
    ok(norm_indexes[0] == 0);
    ok(norm_indexes[1] == 1);
    norm_indexes = NULL;

    input = h2o_iovec_init(H2O_STRLIT("aa"));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 3);
    ok(memcmp(b.base, H2O_STRLIT("/aa")) == 0);
    ok(q == SIZE_MAX);
    ok(norm_indexes != NULL);
    ok(norm_indexes[0] == 0);
    ok(norm_indexes[1] == 1);
    ok(norm_indexes[2] == 2);
    norm_indexes = NULL;

    input = h2o_iovec_init(H2O_STRLIT("/"));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 1);
    ok(memcmp(b.base, H2O_STRLIT("/")) == 0);
    ok(q == SIZE_MAX);
    ok(norm_indexes == NULL);

    input = h2o_iovec_init(H2O_STRLIT("/."));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 1);
    ok(memcmp(b.base, H2O_STRLIT("/")) == 0);
    ok(q == SIZE_MAX);
    ok(norm_indexes != NULL);
    ok(norm_indexes[0] == 1);
    norm_indexes = NULL;

    input = h2o_iovec_init(H2O_STRLIT("/./"));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 1);
    ok(memcmp(b.base, H2O_STRLIT("/")) == 0);
    ok(q == SIZE_MAX);
    ok(norm_indexes != NULL);
    ok(norm_indexes[0] == 1);
    norm_indexes = NULL;

    input = h2o_iovec_init(H2O_STRLIT("/.."));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 1);
    ok(memcmp(b.base, H2O_STRLIT("/")) == 0);
    ok(q == SIZE_MAX);
    ok(norm_indexes != NULL);
    ok(norm_indexes[0] == 1);
    norm_indexes = NULL;

    input = h2o_iovec_init(H2O_STRLIT("/../"));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 1);
    ok(memcmp(b.base, H2O_STRLIT("/")) == 0);
    ok(q == SIZE_MAX);
    ok(norm_indexes != NULL);
    ok(norm_indexes[0] == 1);
    norm_indexes = NULL;

    input = h2o_iovec_init(H2O_STRLIT("/abc"));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 4);
    ok(memcmp(b.base, H2O_STRLIT("/abc")) == 0);
    ok(q == SIZE_MAX);
    ok(norm_indexes == NULL);

    input = h2o_iovec_init(H2O_STRLIT("/abc"));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 4);
    ok(memcmp(b.base, H2O_STRLIT("/abc")) == 0);
    ok(q == SIZE_MAX);
    ok(norm_indexes == NULL);

    input = h2o_iovec_init(H2O_STRLIT("/abc/../def"));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 4);
    ok(memcmp(b.base, H2O_STRLIT("/def")) == 0);
    ok(q == SIZE_MAX);
    ok(norm_indexes != NULL);
    ok(norm_indexes[0] == 1);
    ok(norm_indexes[1] == 9);
    ok(norm_indexes[2] == 10);
    ok(norm_indexes[3] == 11);
    norm_indexes = NULL;

    input = h2o_iovec_init(H2O_STRLIT("/abc/../../def"));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 4);
    ok(memcmp(b.base, H2O_STRLIT("/def")) == 0);
    ok(q == SIZE_MAX);
    ok(norm_indexes != NULL);
    ok(norm_indexes[0] == 1);
    ok(norm_indexes[1] == 12);
    ok(norm_indexes[2] == 13);
    ok(norm_indexes[3] == 14);
    norm_indexes = NULL;

    input = h2o_iovec_init(H2O_STRLIT("/abc/./def"));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 8);
    ok(memcmp(b.base, H2O_STRLIT("/abc/def")) == 0);
    ok(q == SIZE_MAX);
    ok(norm_indexes != NULL);
    ok(norm_indexes[0] == 1);
    ok(norm_indexes[1] == 2);
    ok(norm_indexes[2] == 3);
    ok(norm_indexes[3] == 4);
    ok(norm_indexes[4] == 5);
    ok(norm_indexes[5] == 8);
    ok(norm_indexes[6] == 9);
    ok(norm_indexes[7] == 10);
    norm_indexes = NULL;

    input = h2o_iovec_init(H2O_STRLIT("/abc/././def"));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 8);
    ok(memcmp(b.base, H2O_STRLIT("/abc/def")) == 0);
    ok(q == SIZE_MAX);
    ok(norm_indexes != NULL);
    ok(norm_indexes[0] == 1);
    ok(norm_indexes[1] == 2);
    ok(norm_indexes[2] == 3);
    ok(norm_indexes[3] == 4);
    ok(norm_indexes[4] == 5);
    ok(norm_indexes[5] == 10);
    ok(norm_indexes[6] == 11);
    ok(norm_indexes[7] == 12);
    norm_indexes = NULL;

    input = h2o_iovec_init(H2O_STRLIT("/abc/def/ghi/../.."));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 5);
    ok(memcmp(b.base, H2O_STRLIT("/abc/")) == 0);
    ok(q == SIZE_MAX);
    ok(norm_indexes != NULL);
    ok(norm_indexes[0] == 1);
    ok(norm_indexes[1] == 2);
    ok(norm_indexes[2] == 3);
    ok(norm_indexes[3] == 4);
    ok(norm_indexes[4] == 5);
    norm_indexes = NULL;

    input = h2o_iovec_init(H2O_STRLIT("/abc/def/./."));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 9);
    ok(memcmp(b.base, H2O_STRLIT("/abc/def/")) == 0);
    ok(q == SIZE_MAX);
    ok(norm_indexes != NULL);
    ok(norm_indexes[0] == 1);
    ok(norm_indexes[1] == 2);
    ok(norm_indexes[2] == 3);
    ok(norm_indexes[3] == 4);
    ok(norm_indexes[4] == 5);
    ok(norm_indexes[5] == 6);
    ok(norm_indexes[6] == 7);
    ok(norm_indexes[7] == 8);
    norm_indexes = NULL;

    input = h2o_iovec_init(H2O_STRLIT("/abc/def/ghi/../."));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 9);
    ok(memcmp(b.base, H2O_STRLIT("/abc/def/")) == 0);
    ok(q == SIZE_MAX);
    ok(norm_indexes != NULL);
    ok(norm_indexes[0] == 1);
    ok(norm_indexes[1] == 2);
    ok(norm_indexes[2] == 3);
    ok(norm_indexes[3] == 4);
    ok(norm_indexes[4] == 5);
    ok(norm_indexes[5] == 6);
    ok(norm_indexes[6] == 7);
    ok(norm_indexes[7] == 8);
    norm_indexes = NULL;

    input = h2o_iovec_init(H2O_STRLIT("/abc/def/./.."));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 5);
    ok(memcmp(b.base, H2O_STRLIT("/abc/")) == 0);
    ok(q == SIZE_MAX);
    ok(norm_indexes != NULL);
    ok(norm_indexes[0] == 1);
    ok(norm_indexes[1] == 2);
    ok(norm_indexes[2] == 3);
    ok(norm_indexes[3] == 4);
    ok(norm_indexes[4] == 5);
    norm_indexes = NULL;

    input = h2o_iovec_init(H2O_STRLIT("/abc/def/.."));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 5);
    ok(memcmp(b.base, H2O_STRLIT("/abc/")) == 0);
    ok(q == SIZE_MAX);
    ok(norm_indexes != NULL);
    ok(norm_indexes[0] == 1);
    ok(norm_indexes[1] == 2);
    ok(norm_indexes[2] == 3);
    ok(norm_indexes[3] == 4);
    ok(norm_indexes[4] == 5);
    norm_indexes = NULL;

    input = h2o_iovec_init(H2O_STRLIT("/abc/def/."));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 9);
    ok(memcmp(b.base, H2O_STRLIT("/abc/def/")) == 0);
    ok(q == SIZE_MAX);
    ok(norm_indexes != NULL);
    ok(norm_indexes[0] == 1);
    ok(norm_indexes[1] == 2);
    ok(norm_indexes[2] == 3);
    ok(norm_indexes[3] == 4);
    ok(norm_indexes[4] == 5);
    ok(norm_indexes[5] == 6);
    ok(norm_indexes[6] == 7);
    norm_indexes = NULL;

    input = h2o_iovec_init(H2O_STRLIT("/abc?xx"));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 4);
    ok(memcmp(b.base, H2O_STRLIT("/abc")) == 0);
    ok(q == 4);
    ok(norm_indexes == NULL);

    input = h2o_iovec_init(H2O_STRLIT("/abc/../def?xx"));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 4);
    ok(memcmp(b.base, H2O_STRLIT("/def")) == 0);
    ok(q == 11);
    ok(norm_indexes != NULL);
    ok(norm_indexes[0] == 1);
    ok(norm_indexes[1] == 9);
    ok(norm_indexes[2] == 10);
    ok(norm_indexes[3] == 11);
    norm_indexes = NULL;

    input = h2o_iovec_init(H2O_STRLIT("/a%62c"));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 4);
    ok(memcmp(b.base, H2O_STRLIT("/abc")) == 0);
    ok(q == SIZE_MAX);
    ok(norm_indexes != NULL);
    ok(norm_indexes[0] == 1);
    ok(norm_indexes[1] == 2);
    ok(norm_indexes[2] == 5);
    ok(norm_indexes[3] == 6);
    norm_indexes = NULL;

    input = h2o_iovec_init(H2O_STRLIT("/a%6"));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 4);
    ok(memcmp(b.base, H2O_STRLIT("/a%6")) == 0);
    ok(q == SIZE_MAX);
    ok(norm_indexes != NULL);
    ok(norm_indexes[0] == 1);
    ok(norm_indexes[1] == 2);
    ok(norm_indexes[2] == 3);
    ok(norm_indexes[3] == 4);
    norm_indexes = NULL;

    input = h2o_iovec_init(H2O_STRLIT("/a%6?"));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 4);
    ok(memcmp(b.base, H2O_STRLIT("/a%6")) == 0);
    ok(q == 4);
    ok(norm_indexes != NULL);
    ok(norm_indexes[0] == 1);
    ok(norm_indexes[1] == 2);
    ok(norm_indexes[2] == 3);
    ok(norm_indexes[3] == 4);
    norm_indexes = NULL;

    input = h2o_iovec_init(H2O_STRLIT("/%25"));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 2);
    ok(memcmp(b.base, H2O_STRLIT("/%")) == 0);
    ok(q == SIZE_MAX);
    ok(norm_indexes != NULL);
    ok(norm_indexes[0] == 1);
    ok(norm_indexes[1] == 4);
    norm_indexes = NULL;

    input = h2o_iovec_init(H2O_STRLIT("/abc//"));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 6);
    ok(memcmp(b.base, H2O_STRLIT("/abc//")) == 0);
    ok(q == SIZE_MAX);
    ok(norm_indexes == NULL);

    input = h2o_iovec_init(H2O_STRLIT("/abc//d"));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 7);
    ok(memcmp(b.base, H2O_STRLIT("/abc//d")) == 0);
    ok(q == SIZE_MAX);
    ok(norm_indexes == NULL);

    input = h2o_iovec_init(H2O_STRLIT("//"));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 2);
    ok(memcmp(b.base, H2O_STRLIT("//")) == 0);
    ok(q == SIZE_MAX);
    ok(norm_indexes == NULL);

    input = h2o_iovec_init(H2O_STRLIT("//abc"));
    b = h2o_url_normalize_path(&pool, input.base, input.len, &q, &norm_indexes);
    ok(b.len == 5);
    ok(memcmp(b.base, H2O_STRLIT("//abc")) == 0);
    ok(q == SIZE_MAX);
    ok(norm_indexes == NULL);

    h2o_mem_clear_pool(&pool);
}
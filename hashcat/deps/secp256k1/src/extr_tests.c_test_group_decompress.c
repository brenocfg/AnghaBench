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
typedef  int /*<<< orphan*/  secp256k1_gej ;
struct TYPE_5__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  infinity; } ;
typedef  TYPE_1__ secp256k1_ge ;
typedef  int /*<<< orphan*/  secp256k1_fe ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 int /*<<< orphan*/  random_fe_test (int /*<<< orphan*/ *) ; 
 int secp256k1_fe_equal_var (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int secp256k1_fe_is_odd (int /*<<< orphan*/ *) ; 
 int secp256k1_fe_is_quad_var (int /*<<< orphan*/ *) ; 
 scalar_t__ secp256k1_fe_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_normalize_var (int /*<<< orphan*/ *) ; 
 int secp256k1_ge_set_xo_var (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int secp256k1_ge_set_xquad (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int secp256k1_gej_has_quad_y_var (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_gej_neg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_gej_rescale (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_gej_set_ge (int /*<<< orphan*/ *,TYPE_1__*) ; 

void test_group_decompress(const secp256k1_fe* x) {
    /* The input itself, normalized. */
    secp256k1_fe fex = *x;
    secp256k1_fe fez;
    /* Results of set_xquad_var, set_xo_var(..., 0), set_xo_var(..., 1). */
    secp256k1_ge ge_quad, ge_even, ge_odd;
    secp256k1_gej gej_quad;
    /* Return values of the above calls. */
    int res_quad, res_even, res_odd;

    secp256k1_fe_normalize_var(&fex);

    res_quad = secp256k1_ge_set_xquad(&ge_quad, &fex);
    res_even = secp256k1_ge_set_xo_var(&ge_even, &fex, 0);
    res_odd = secp256k1_ge_set_xo_var(&ge_odd, &fex, 1);

    CHECK(res_quad == res_even);
    CHECK(res_quad == res_odd);

    if (res_quad) {
        secp256k1_fe_normalize_var(&ge_quad.x);
        secp256k1_fe_normalize_var(&ge_odd.x);
        secp256k1_fe_normalize_var(&ge_even.x);
        secp256k1_fe_normalize_var(&ge_quad.y);
        secp256k1_fe_normalize_var(&ge_odd.y);
        secp256k1_fe_normalize_var(&ge_even.y);

        /* No infinity allowed. */
        CHECK(!ge_quad.infinity);
        CHECK(!ge_even.infinity);
        CHECK(!ge_odd.infinity);

        /* Check that the x coordinates check out. */
        CHECK(secp256k1_fe_equal_var(&ge_quad.x, x));
        CHECK(secp256k1_fe_equal_var(&ge_even.x, x));
        CHECK(secp256k1_fe_equal_var(&ge_odd.x, x));

        /* Check that the Y coordinate result in ge_quad is a square. */
        CHECK(secp256k1_fe_is_quad_var(&ge_quad.y));

        /* Check odd/even Y in ge_odd, ge_even. */
        CHECK(secp256k1_fe_is_odd(&ge_odd.y));
        CHECK(!secp256k1_fe_is_odd(&ge_even.y));

        /* Check secp256k1_gej_has_quad_y_var. */
        secp256k1_gej_set_ge(&gej_quad, &ge_quad);
        CHECK(secp256k1_gej_has_quad_y_var(&gej_quad));
        do {
            random_fe_test(&fez);
        } while (secp256k1_fe_is_zero(&fez));
        secp256k1_gej_rescale(&gej_quad, &fez);
        CHECK(secp256k1_gej_has_quad_y_var(&gej_quad));
        secp256k1_gej_neg(&gej_quad, &gej_quad);
        CHECK(!secp256k1_gej_has_quad_y_var(&gej_quad));
        do {
            random_fe_test(&fez);
        } while (secp256k1_fe_is_zero(&fez));
        secp256k1_gej_rescale(&gej_quad, &fez);
        CHECK(!secp256k1_gej_has_quad_y_var(&gej_quad));
        secp256k1_gej_neg(&gej_quad, &gej_quad);
        CHECK(secp256k1_gej_has_quad_y_var(&gej_quad));
    }
}
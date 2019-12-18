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
typedef  int /*<<< orphan*/  bench_inv ;

/* Variables and functions */
 int /*<<< orphan*/  bench_context_sign ; 
 int /*<<< orphan*/  bench_context_verify ; 
 int /*<<< orphan*/  bench_ecmult_wnaf ; 
 int /*<<< orphan*/  bench_field_inverse ; 
 int /*<<< orphan*/  bench_field_inverse_var ; 
 int /*<<< orphan*/  bench_field_mul ; 
 int /*<<< orphan*/  bench_field_normalize ; 
 int /*<<< orphan*/  bench_field_normalize_weak ; 
 int /*<<< orphan*/  bench_field_sqr ; 
 int /*<<< orphan*/  bench_field_sqrt ; 
 int /*<<< orphan*/  bench_group_add_affine ; 
 int /*<<< orphan*/  bench_group_add_affine_var ; 
 int /*<<< orphan*/  bench_group_add_var ; 
 int /*<<< orphan*/  bench_group_double_var ; 
 int /*<<< orphan*/  bench_group_jacobi_var ; 
 int /*<<< orphan*/  bench_hmac_sha256 ; 
 int /*<<< orphan*/  bench_num_jacobi ; 
 int /*<<< orphan*/  bench_rfc6979_hmac_sha256 ; 
 int /*<<< orphan*/  bench_scalar_add ; 
 int /*<<< orphan*/  bench_scalar_inverse ; 
 int /*<<< orphan*/  bench_scalar_inverse_var ; 
 int /*<<< orphan*/  bench_scalar_mul ; 
 int /*<<< orphan*/  bench_scalar_negate ; 
 int /*<<< orphan*/  bench_scalar_split ; 
 int /*<<< orphan*/  bench_scalar_sqr ; 
 int /*<<< orphan*/  bench_setup ; 
 int /*<<< orphan*/  bench_sha256 ; 
 int /*<<< orphan*/  bench_wnaf_const ; 
 scalar_t__ have_flag (int,char**,char*) ; 
 int /*<<< orphan*/  run_benchmark (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

int main(int argc, char **argv) {
    bench_inv data;
    if (have_flag(argc, argv, "scalar") || have_flag(argc, argv, "add")) run_benchmark("scalar_add", bench_scalar_add, bench_setup, NULL, &data, 10, 2000000);
    if (have_flag(argc, argv, "scalar") || have_flag(argc, argv, "negate")) run_benchmark("scalar_negate", bench_scalar_negate, bench_setup, NULL, &data, 10, 2000000);
    if (have_flag(argc, argv, "scalar") || have_flag(argc, argv, "sqr")) run_benchmark("scalar_sqr", bench_scalar_sqr, bench_setup, NULL, &data, 10, 200000);
    if (have_flag(argc, argv, "scalar") || have_flag(argc, argv, "mul")) run_benchmark("scalar_mul", bench_scalar_mul, bench_setup, NULL, &data, 10, 200000);
#ifdef USE_ENDOMORPHISM
    if (have_flag(argc, argv, "scalar") || have_flag(argc, argv, "split")) run_benchmark("scalar_split", bench_scalar_split, bench_setup, NULL, &data, 10, 20000);
#endif
    if (have_flag(argc, argv, "scalar") || have_flag(argc, argv, "inverse")) run_benchmark("scalar_inverse", bench_scalar_inverse, bench_setup, NULL, &data, 10, 2000);
    if (have_flag(argc, argv, "scalar") || have_flag(argc, argv, "inverse")) run_benchmark("scalar_inverse_var", bench_scalar_inverse_var, bench_setup, NULL, &data, 10, 2000);

    if (have_flag(argc, argv, "field") || have_flag(argc, argv, "normalize")) run_benchmark("field_normalize", bench_field_normalize, bench_setup, NULL, &data, 10, 2000000);
    if (have_flag(argc, argv, "field") || have_flag(argc, argv, "normalize")) run_benchmark("field_normalize_weak", bench_field_normalize_weak, bench_setup, NULL, &data, 10, 2000000);
    if (have_flag(argc, argv, "field") || have_flag(argc, argv, "sqr")) run_benchmark("field_sqr", bench_field_sqr, bench_setup, NULL, &data, 10, 200000);
    if (have_flag(argc, argv, "field") || have_flag(argc, argv, "mul")) run_benchmark("field_mul", bench_field_mul, bench_setup, NULL, &data, 10, 200000);
    if (have_flag(argc, argv, "field") || have_flag(argc, argv, "inverse")) run_benchmark("field_inverse", bench_field_inverse, bench_setup, NULL, &data, 10, 20000);
    if (have_flag(argc, argv, "field") || have_flag(argc, argv, "inverse")) run_benchmark("field_inverse_var", bench_field_inverse_var, bench_setup, NULL, &data, 10, 20000);
    if (have_flag(argc, argv, "field") || have_flag(argc, argv, "sqrt")) run_benchmark("field_sqrt", bench_field_sqrt, bench_setup, NULL, &data, 10, 20000);

    if (have_flag(argc, argv, "group") || have_flag(argc, argv, "double")) run_benchmark("group_double_var", bench_group_double_var, bench_setup, NULL, &data, 10, 200000);
    if (have_flag(argc, argv, "group") || have_flag(argc, argv, "add")) run_benchmark("group_add_var", bench_group_add_var, bench_setup, NULL, &data, 10, 200000);
    if (have_flag(argc, argv, "group") || have_flag(argc, argv, "add")) run_benchmark("group_add_affine", bench_group_add_affine, bench_setup, NULL, &data, 10, 200000);
    if (have_flag(argc, argv, "group") || have_flag(argc, argv, "add")) run_benchmark("group_add_affine_var", bench_group_add_affine_var, bench_setup, NULL, &data, 10, 200000);
    if (have_flag(argc, argv, "group") || have_flag(argc, argv, "jacobi")) run_benchmark("group_jacobi_var", bench_group_jacobi_var, bench_setup, NULL, &data, 10, 20000);

    if (have_flag(argc, argv, "ecmult") || have_flag(argc, argv, "wnaf")) run_benchmark("wnaf_const", bench_wnaf_const, bench_setup, NULL, &data, 10, 20000);
    if (have_flag(argc, argv, "ecmult") || have_flag(argc, argv, "wnaf")) run_benchmark("ecmult_wnaf", bench_ecmult_wnaf, bench_setup, NULL, &data, 10, 20000);

    if (have_flag(argc, argv, "hash") || have_flag(argc, argv, "sha256")) run_benchmark("hash_sha256", bench_sha256, bench_setup, NULL, &data, 10, 20000);
    if (have_flag(argc, argv, "hash") || have_flag(argc, argv, "hmac")) run_benchmark("hash_hmac_sha256", bench_hmac_sha256, bench_setup, NULL, &data, 10, 20000);
    if (have_flag(argc, argv, "hash") || have_flag(argc, argv, "rng6979")) run_benchmark("hash_rfc6979_hmac_sha256", bench_rfc6979_hmac_sha256, bench_setup, NULL, &data, 10, 20000);

    if (have_flag(argc, argv, "context") || have_flag(argc, argv, "verify")) run_benchmark("context_verify", bench_context_verify, bench_setup, NULL, &data, 10, 20);
    if (have_flag(argc, argv, "context") || have_flag(argc, argv, "sign")) run_benchmark("context_sign", bench_context_sign, bench_setup, NULL, &data, 10, 200);

#ifndef USE_NUM_NONE
    if (have_flag(argc, argv, "num") || have_flag(argc, argv, "jacobi")) run_benchmark("num_jacobi", bench_num_jacobi, bench_setup, NULL, &data, 10, 200000);
#endif
    return 0;
}
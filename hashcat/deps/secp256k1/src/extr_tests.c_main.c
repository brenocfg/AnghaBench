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
typedef  unsigned char uint64_t ;
typedef  int /*<<< orphan*/  seed16 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 int SECP256K1_CONTEXT_SIGN ; 
 int SECP256K1_CONTEXT_VERIFY ; 
 int count ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int fread (unsigned char**,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  run_context_tests (int) ; 
 int /*<<< orphan*/  run_ec_combine () ; 
 int /*<<< orphan*/  run_ec_pubkey_parse_test () ; 
 int /*<<< orphan*/  run_ecdh_tests () ; 
 int /*<<< orphan*/  run_ecdsa_der_parse () ; 
 int /*<<< orphan*/  run_ecdsa_edge_cases () ; 
 int /*<<< orphan*/  run_ecdsa_end_to_end () ; 
 int /*<<< orphan*/  run_ecdsa_openssl () ; 
 int /*<<< orphan*/  run_ecdsa_sign_verify () ; 
 int /*<<< orphan*/  run_eckey_edge_case_test () ; 
 int /*<<< orphan*/  run_ecmult_chain () ; 
 int /*<<< orphan*/  run_ecmult_const_tests () ; 
 int /*<<< orphan*/  run_ecmult_constants () ; 
 int /*<<< orphan*/  run_ecmult_gen_blind () ; 
 int /*<<< orphan*/  run_ecmult_multi_tests () ; 
 int /*<<< orphan*/  run_endomorphism_tests () ; 
 int /*<<< orphan*/  run_field_convert () ; 
 int /*<<< orphan*/  run_field_inv () ; 
 int /*<<< orphan*/  run_field_inv_all_var () ; 
 int /*<<< orphan*/  run_field_inv_var () ; 
 int /*<<< orphan*/  run_field_misc () ; 
 int /*<<< orphan*/  run_ge () ; 
 int /*<<< orphan*/  run_group_decompress () ; 
 int /*<<< orphan*/  run_hmac_sha256_tests () ; 
 int /*<<< orphan*/  run_num_smalltests () ; 
 int /*<<< orphan*/  run_point_times_order () ; 
 int /*<<< orphan*/  run_rand_bits () ; 
 int /*<<< orphan*/  run_rand_int () ; 
 int /*<<< orphan*/  run_random_pubkeys () ; 
 int /*<<< orphan*/  run_recovery_tests () ; 
 int /*<<< orphan*/  run_rfc6979_hmac_sha256_tests () ; 
 int /*<<< orphan*/  run_scalar_tests () ; 
 int /*<<< orphan*/  run_scratch_tests () ; 
 int /*<<< orphan*/  run_sha256_tests () ; 
 int /*<<< orphan*/  run_sqr () ; 
 int /*<<< orphan*/  run_sqrt () ; 
 int /*<<< orphan*/  run_wnaf () ; 
 int /*<<< orphan*/  secp256k1_context_create (int) ; 
 int /*<<< orphan*/  secp256k1_context_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  secp256k1_context_randomize (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  secp256k1_rand256 (unsigned char*) ; 
 scalar_t__ secp256k1_rand_bits (int) ; 
 int /*<<< orphan*/  secp256k1_rand_seed (unsigned char*) ; 
 int sscanf (char const*,char*,unsigned short*) ; 
 int /*<<< orphan*/  stderr ; 
 int strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned char time (int /*<<< orphan*/ *) ; 

int main(int argc, char **argv) {
    unsigned char seed16[16] = {0};
    unsigned char run32[32] = {0};
    /* find iteration count */
    if (argc > 1) {
        count = strtol(argv[1], NULL, 0);
    }

    /* find random seed */
    if (argc > 2) {
        int pos = 0;
        const char* ch = argv[2];
        while (pos < 16 && ch[0] != 0 && ch[1] != 0) {
            unsigned short sh;
            if ((sscanf(ch, "%2hx", &sh)) == 1) {
                seed16[pos] = sh;
            } else {
                break;
            }
            ch += 2;
            pos++;
        }
    } else {
        FILE *frand = fopen("/dev/urandom", "r");
        if ((frand == NULL) || fread(&seed16, 1, sizeof(seed16), frand) != sizeof(seed16)) {
            uint64_t t = time(NULL) * (uint64_t)1337;
            fprintf(stderr, "WARNING: could not read 16 bytes from /dev/urandom; falling back to insecure PRNG\n");
            seed16[0] ^= t;
            seed16[1] ^= t >> 8;
            seed16[2] ^= t >> 16;
            seed16[3] ^= t >> 24;
            seed16[4] ^= t >> 32;
            seed16[5] ^= t >> 40;
            seed16[6] ^= t >> 48;
            seed16[7] ^= t >> 56;
        }
        if (frand) {
            fclose(frand);
        }
    }
    secp256k1_rand_seed(seed16);

    printf("test count = %i\n", count);
    printf("random seed = %02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n", seed16[0], seed16[1], seed16[2], seed16[3], seed16[4], seed16[5], seed16[6], seed16[7], seed16[8], seed16[9], seed16[10], seed16[11], seed16[12], seed16[13], seed16[14], seed16[15]);

    /* initialize */
    run_context_tests(0);
    run_context_tests(1);
    run_scratch_tests();
    ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY);
    if (secp256k1_rand_bits(1)) {
        secp256k1_rand256(run32);
        CHECK(secp256k1_context_randomize(ctx, secp256k1_rand_bits(1) ? run32 : NULL));
    }

    run_rand_bits();
    run_rand_int();

    run_sha256_tests();
    run_hmac_sha256_tests();
    run_rfc6979_hmac_sha256_tests();

#ifndef USE_NUM_NONE
    /* num tests */
    run_num_smalltests();
#endif

    /* scalar tests */
    run_scalar_tests();

    /* field tests */
    run_field_inv();
    run_field_inv_var();
    run_field_inv_all_var();
    run_field_misc();
    run_field_convert();
    run_sqr();
    run_sqrt();

    /* group tests */
    run_ge();
    run_group_decompress();

    /* ecmult tests */
    run_wnaf();
    run_point_times_order();
    run_ecmult_chain();
    run_ecmult_constants();
    run_ecmult_gen_blind();
    run_ecmult_const_tests();
    run_ecmult_multi_tests();
    run_ec_combine();

    /* endomorphism tests */
#ifdef USE_ENDOMORPHISM
    run_endomorphism_tests();
#endif

    /* EC point parser test */
    run_ec_pubkey_parse_test();

    /* EC key edge cases */
    run_eckey_edge_case_test();

#ifdef ENABLE_MODULE_ECDH
    /* ecdh tests */
    run_ecdh_tests();
#endif

    /* ecdsa tests */
    run_random_pubkeys();
    run_ecdsa_der_parse();
    run_ecdsa_sign_verify();
    run_ecdsa_end_to_end();
    run_ecdsa_edge_cases();
#ifdef ENABLE_OPENSSL_TESTS
    run_ecdsa_openssl();
#endif

#ifdef ENABLE_MODULE_RECOVERY
    /* ECDSA pubkey recovery tests */
    run_recovery_tests();
#endif

    secp256k1_rand256(run32);
    printf("random run = %02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n", run32[0], run32[1], run32[2], run32[3], run32[4], run32[5], run32[6], run32[7], run32[8], run32[9], run32[10], run32[11], run32[12], run32[13], run32[14], run32[15]);

    /* shutdown */
    secp256k1_context_destroy(ctx);

    printf("no problems found\n");
    return 0;
}
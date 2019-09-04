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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  cf_aes_context ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_CHECK (int) ; 
 int /*<<< orphan*/  cf_aes ; 
 int /*<<< orphan*/  cf_aes_init (int /*<<< orphan*/ *,size_t*,size_t) ; 
 int /*<<< orphan*/  cf_ocb_encrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,size_t,size_t*,size_t,size_t*,int,size_t*,size_t*,size_t) ; 
 scalar_t__ memcmp (size_t*,void const*,size_t) ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write32_be (int,size_t*) ; 

__attribute__((used)) static void check_ocb_long(size_t nkey, const void *expect_tag, size_t ntag)
{
  uint8_t C[22400];
  uint8_t K[32];
  uint8_t S[128] = { 0 };
  uint8_t N[12] = { 0 };
  size_t nC = 0;

  memset(K, 0, sizeof K);
  K[nkey - 1] = ntag * 8;

  cf_aes_context aes;
  cf_aes_init(&aes, K, nkey);

  for (size_t i = 0; i < 128; i++)
  {
    /* N = num2str(3i+1, 96) */
    memset(N, 0, sizeof N);
    write32_be(3 * i + 1, N + 8);

    /* C = C || OCB-ENCRYPT(K, N, S, S)
     * nb. OCB-ENCRYPT(Key, Nonce, AAD, Plain) */
    cf_ocb_encrypt(&cf_aes, &aes,
                   S, i,        /* plain */
                   S, i,        /* aad */
                   N, sizeof N, /* nonce */
                   C + nC,      /* cipher out */
                   C + nC + i,  /* tag out */
                   ntag);
    nC += i + ntag;

    /* N = num2str(3i+2,96) */
    write32_be(3 * i + 2, N + 8);

    /* C = C || OCB-ENCRYPT(K, N, <empty string>, S) */
    cf_ocb_encrypt(&cf_aes, &aes,
                   S, i,
                   NULL, 0,
                   N, sizeof N,
                   C + nC,
                   C + nC + i,
                   ntag);
    nC += i + ntag;

    /* N = num2str(3i+3,96) */
    write32_be(3 * i + 3, N + 8);

    /* C = C || OCB-ENCRYPT(K, N, S, <empty string>) */
    cf_ocb_encrypt(&cf_aes, &aes,
                   NULL, 0,
                   S, i,
                   N, sizeof N,
                   NULL,
                   C + nC,
                   ntag);
    nC += ntag;
  }

  /* N = num2str(385, 96) */
  write32_be(385, N + 8);

  /* Output : OCB-ENCRYPT(K, N, C, <empty string>) */
  uint8_t result[16];
  cf_ocb_encrypt(&cf_aes, &aes,
                 NULL, 0,
                 C, nC,
                 N, sizeof N,
                 NULL,
                 result, ntag);

  TEST_CHECK(memcmp(result, expect_tag, ntag) == 0);
}
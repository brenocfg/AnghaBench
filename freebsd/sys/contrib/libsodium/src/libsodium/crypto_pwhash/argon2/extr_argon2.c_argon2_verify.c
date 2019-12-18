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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  argon2_type ;
struct TYPE_4__ {int /*<<< orphan*/ * out; void* outlen; int /*<<< orphan*/ * salt; int /*<<< orphan*/ * ad; void* saltlen; int /*<<< orphan*/  threads; int /*<<< orphan*/  m_cost; int /*<<< orphan*/  t_cost; void* adlen; scalar_t__ secretlen; int /*<<< orphan*/ * secret; scalar_t__ pwdlen; int /*<<< orphan*/ * pwd; } ;
typedef  TYPE_1__ argon2_context ;

/* Variables and functions */
 int ARGON2_DECODING_LENGTH_FAIL ; 
 int ARGON2_MEMORY_ALLOCATION_ERROR ; 
 int ARGON2_OK ; 
 int ARGON2_VERIFY_MISMATCH ; 
 size_t UINT32_MAX ; 
 int argon2_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,size_t const,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int decode_string (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (void*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sodium_memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 size_t strlen (char const*) ; 

int
argon2_verify(const char *encoded, const void *pwd, const size_t pwdlen,
              argon2_type type)
{
    argon2_context ctx;
    uint8_t       *out;
    int            decode_result;
    int            ret;
    size_t         encoded_len;

    memset(&ctx, 0, sizeof ctx);

    ctx.pwd       = NULL;
    ctx.pwdlen    = 0;
    ctx.secret    = NULL;
    ctx.secretlen = 0;

    /* max values, to be updated in decode_string */
    encoded_len = strlen(encoded);
    if (encoded_len > UINT32_MAX) {
        return ARGON2_DECODING_LENGTH_FAIL;
    }
    ctx.adlen   = (uint32_t) encoded_len;
    ctx.saltlen = (uint32_t) encoded_len;
    ctx.outlen  = (uint32_t) encoded_len;

    ctx.ad   = (uint8_t *) malloc(ctx.adlen);
    ctx.salt = (uint8_t *) malloc(ctx.saltlen);
    ctx.out  = (uint8_t *) malloc(ctx.outlen);
    if (!ctx.out || !ctx.salt || !ctx.ad) {
        free(ctx.ad);
        free(ctx.salt);
        free(ctx.out);
        return ARGON2_MEMORY_ALLOCATION_ERROR;
    }
    out = (uint8_t *) malloc(ctx.outlen);
    if (!out) {
        free(ctx.ad);
        free(ctx.salt);
        free(ctx.out);
        return ARGON2_MEMORY_ALLOCATION_ERROR;
    }

    decode_result = decode_string(&ctx, encoded, type);
    if (decode_result != ARGON2_OK) {
        free(ctx.ad);
        free(ctx.salt);
        free(ctx.out);
        free(out);
        return decode_result;
    }

    ret = argon2_hash(ctx.t_cost, ctx.m_cost, ctx.threads, pwd, pwdlen,
                      ctx.salt, ctx.saltlen, out, ctx.outlen, NULL, 0, type);

    free(ctx.ad);
    free(ctx.salt);

    if (ret != ARGON2_OK || sodium_memcmp(out, ctx.out, ctx.outlen) != 0) {
        ret = ARGON2_VERIFY_MISMATCH;
    }
    free(out);
    free(ctx.out);

    return ret;
}
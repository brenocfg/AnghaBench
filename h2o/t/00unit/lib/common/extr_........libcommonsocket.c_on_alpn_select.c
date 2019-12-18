#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ len; scalar_t__ base; } ;
typedef  TYPE_1__ h2o_iovec_t ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int SSL_TLSEXT_ERR_NOACK ; 
 int SSL_TLSEXT_ERR_OK ; 
 scalar_t__ memcmp (unsigned char const*,scalar_t__,size_t) ; 

__attribute__((used)) static int on_alpn_select(SSL *ssl, const unsigned char **out, unsigned char *outlen, const unsigned char *_in, unsigned int inlen,
                          void *_protocols)
{
    const h2o_iovec_t *protocols = _protocols;
    size_t i;

    for (i = 0; protocols[i].len != 0; ++i) {
        const unsigned char *in = _in, *in_end = in + inlen;
        while (in != in_end) {
            size_t cand_len = *in++;
            if (in_end - in < cand_len) {
                /* broken request */
                return SSL_TLSEXT_ERR_NOACK;
            }
            if (cand_len == protocols[i].len && memcmp(in, protocols[i].base, cand_len) == 0) {
                goto Found;
            }
            in += cand_len;
        }
    }
    /* not found */
    return SSL_TLSEXT_ERR_NOACK;

Found:
    *out = (const unsigned char *)protocols[i].base;
    *outlen = (unsigned char)protocols[i].len;
    return SSL_TLSEXT_ERR_OK;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ l ;
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ EVP_ENCODE_CTX ;

/* Variables and functions */
 scalar_t__ B64_NOT_BASE64 (int) ; 
 int B64_WS ; 
 int EVP_ENCODE_CTX_USE_SRP_ALPHABET ; 
 int conv_ascii2bin (unsigned char const,unsigned char const*) ; 
 unsigned char* data_ascii2bin ; 
 unsigned char* srpdata_ascii2bin ; 

__attribute__((used)) static int evp_decodeblock_int(EVP_ENCODE_CTX *ctx, unsigned char *t,
                               const unsigned char *f, int n)
{
    int i, ret = 0, a, b, c, d;
    unsigned long l;
    const unsigned char *table;

    if (ctx != NULL && (ctx->flags & EVP_ENCODE_CTX_USE_SRP_ALPHABET) != 0)
        table = srpdata_ascii2bin;
    else
        table = data_ascii2bin;

    /* trim white space from the start of the line. */
    while ((conv_ascii2bin(*f, table) == B64_WS) && (n > 0)) {
        f++;
        n--;
    }

    /*
     * strip off stuff at the end of the line ascii2bin values B64_WS,
     * B64_EOLN, B64_EOLN and B64_EOF
     */
    while ((n > 3) && (B64_NOT_BASE64(conv_ascii2bin(f[n - 1], table))))
        n--;

    if (n % 4 != 0)
        return -1;

    for (i = 0; i < n; i += 4) {
        a = conv_ascii2bin(*(f++), table);
        b = conv_ascii2bin(*(f++), table);
        c = conv_ascii2bin(*(f++), table);
        d = conv_ascii2bin(*(f++), table);
        if ((a & 0x80) || (b & 0x80) || (c & 0x80) || (d & 0x80))
            return -1;
        l = ((((unsigned long)a) << 18L) |
             (((unsigned long)b) << 12L) |
             (((unsigned long)c) << 6L) | (((unsigned long)d)));
        *(t++) = (unsigned char)(l >> 16L) & 0xff;
        *(t++) = (unsigned char)(l >> 8L) & 0xff;
        *(t++) = (unsigned char)(l) & 0xff;
        ret += 3;
    }
    return ret;
}
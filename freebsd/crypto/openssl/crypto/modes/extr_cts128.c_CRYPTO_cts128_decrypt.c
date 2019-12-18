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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  (* cbc128_f ) (unsigned char const*,unsigned char*,int,void const*,unsigned char*,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (unsigned char const*,unsigned char*,int,void const*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (unsigned char const*,unsigned char*,int,void const*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (unsigned char const*,unsigned char*,int,void const*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (unsigned char const*,unsigned char*,int,void const*,unsigned char*,int /*<<< orphan*/ ) ; 

size_t CRYPTO_cts128_decrypt(const unsigned char *in, unsigned char *out,
                             size_t len, const void *key,
                             unsigned char ivec[16], cbc128_f cbc)
{
    size_t residue;
    union {
        size_t align;
        unsigned char c[32];
    } tmp;

    if (len <= 16)
        return 0;

    if ((residue = len % 16) == 0)
        residue = 16;

    len -= 16 + residue;

    if (len) {
        (*cbc) (in, out, len, key, ivec, 0);
        in += len;
        out += len;
    }

    memset(tmp.c, 0, sizeof(tmp));
    /*
     * this places in[16] at &tmp.c[16] and decrypted block at &tmp.c[0]
     */
    (*cbc) (in, tmp.c, 16, key, tmp.c + 16, 0);

    memcpy(tmp.c, in + 16, residue);
#if defined(CBC_HANDLES_TRUNCATED_IO)
    (*cbc) (tmp.c, out, 16 + residue, key, ivec, 0);
#else
    (*cbc) (tmp.c, tmp.c, 32, key, ivec, 0);
    memcpy(out, tmp.c, 16 + residue);
#endif
    return 16 + len + residue;
}
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
struct TYPE_3__ {int bytes; scalar_t__ buf; int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ secp256k1_sha256 ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY_CHECK (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  secp256k1_sha256_transform (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void secp256k1_sha256_write(secp256k1_sha256 *hash, const unsigned char *data, size_t len) {
    size_t bufsize = hash->bytes & 0x3F;
    hash->bytes += len;
    VERIFY_CHECK(hash->bytes >= len);
    while (len >= 64 - bufsize) {
        /* Fill the buffer, and process it. */
        size_t chunk_len = 64 - bufsize;
        memcpy(((unsigned char*)hash->buf) + bufsize, data, chunk_len);
        data += chunk_len;
        len -= chunk_len;
        secp256k1_sha256_transform(hash->s, hash->buf);
        bufsize = 0;
    }
    if (len) {
        /* Fill the buffer with what remains. */
        memcpy(((unsigned char*)hash->buf) + bufsize, data, len);
    }
}
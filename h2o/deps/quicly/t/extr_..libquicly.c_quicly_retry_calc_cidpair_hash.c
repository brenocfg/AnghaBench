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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {scalar_t__ len; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ ptls_iovec_t ;
typedef  int /*<<< orphan*/  ptls_hash_algorithm_t ;

/* Variables and functions */
 int PTLS_SHA256_DIGEST_SIZE ; 
 int /*<<< orphan*/  QUICLY_MAX_CID_LEN_V1 ; 
 int /*<<< orphan*/  memcpy (void**,int /*<<< orphan*/ ,scalar_t__) ; 
 int ptls_calc_hash (int /*<<< orphan*/ *,void**,void**,int) ; 
 int /*<<< orphan*/  quicly_decode64 (void*) ; 

int quicly_retry_calc_cidpair_hash(ptls_hash_algorithm_t *sha256, ptls_iovec_t client_cid, ptls_iovec_t server_cid, uint64_t *value)
{
    uint8_t digest[PTLS_SHA256_DIGEST_SIZE], buf[(QUICLY_MAX_CID_LEN_V1 + 1) * 2], *p = buf;
    int ret;

    *p++ = (uint8_t)client_cid.len;
    memcpy(p, client_cid.base, client_cid.len);
    p += client_cid.len;
    *p++ = (uint8_t)server_cid.len;
    memcpy(p, server_cid.base, server_cid.len);
    p += server_cid.len;

    if ((ret = ptls_calc_hash(sha256, digest, buf, p - buf)) != 0)
        return ret;
    p = digest;
    *value = quicly_decode64((void *)&p);

    return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int seq; int /*<<< orphan*/ * aead; } ;
struct TYPE_6__ {TYPE_5__ enc; } ;
struct TYPE_7__ {int needs_key_update; TYPE_1__ traffic_protection; scalar_t__ key_update_send_request; } ;
typedef  TYPE_2__ ptls_t ;
typedef  int /*<<< orphan*/  ptls_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTLS_CONTENT_TYPE_APPDATA ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int buffer_push_encrypted_records (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const*,size_t,TYPE_5__*) ; 
 int update_send_key (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 

int ptls_send(ptls_t *tls, ptls_buffer_t *sendbuf, const void *input, size_t inlen)
{
    assert(tls->traffic_protection.enc.aead != NULL);

    /* "For AES-GCM, up to 2^24.5 full-size records (about 24 million) may be encrypted on a given connection while keeping a
     * safety margin of approximately 2^-57 for Authenticated Encryption (AE) security." (RFC 8446 section 5.5)
     */
    if (tls->traffic_protection.enc.seq >= 16777216)
        tls->needs_key_update = 1;

    if (tls->needs_key_update) {
        int ret;
        if ((ret = update_send_key(tls, sendbuf, tls->key_update_send_request)) != 0)
            return ret;
        tls->needs_key_update = 0;
        tls->key_update_send_request = 0;
    }

    return buffer_push_encrypted_records(sendbuf, PTLS_CONTENT_TYPE_APPDATA, input, inlen, &tls->traffic_protection.enc);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct st_ptls_traffic_protection_t {TYPE_2__* aead; } ;
struct TYPE_9__ {size_t off; size_t* base; } ;
typedef  TYPE_3__ ptls_buffer_t ;
struct TYPE_8__ {TYPE_1__* algo; } ;
struct TYPE_7__ {int tag_size; } ;

/* Variables and functions */
 size_t PTLS_CONTENT_TYPE_APPDATA ; 
 int PTLS_ERROR_NO_MEMORY ; 
 size_t PTLS_MAX_PLAINTEXT_RECORD_SIZE ; 
 size_t aead_encrypt (struct st_ptls_traffic_protection_t*,size_t*,size_t*,size_t,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int buffer_push_encrypted_records (TYPE_3__*,size_t,size_t*,size_t,struct st_ptls_traffic_protection_t*) ; 
 int /*<<< orphan*/  free (size_t*) ; 
 size_t* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t*,size_t) ; 
 int ptls_buffer_reserve (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  ptls_clear_memory (size_t*,size_t) ; 

__attribute__((used)) static int buffer_encrypt_record(ptls_buffer_t *buf, size_t rec_start, struct st_ptls_traffic_protection_t *enc)
{
    size_t bodylen = buf->off - rec_start - 5;
    uint8_t *tmpbuf, type = buf->base[rec_start];
    int ret;

    /* fast path: do in-place encryption if only one record needs to be emitted */
    if (bodylen <= PTLS_MAX_PLAINTEXT_RECORD_SIZE) {
        size_t overhead = 1 + enc->aead->algo->tag_size;
        if ((ret = ptls_buffer_reserve(buf, overhead)) != 0)
            return ret;
        size_t encrypted_len = aead_encrypt(enc, buf->base + rec_start + 5, buf->base + rec_start + 5, bodylen, type);
        assert(encrypted_len == bodylen + overhead);
        buf->off += overhead;
        buf->base[rec_start] = PTLS_CONTENT_TYPE_APPDATA;
        buf->base[rec_start + 3] = (encrypted_len >> 8) & 0xff;
        buf->base[rec_start + 4] = encrypted_len & 0xff;
        return 0;
    }

    /* move plaintext to temporary buffer */
    if ((tmpbuf = malloc(bodylen)) == NULL) {
        ret = PTLS_ERROR_NO_MEMORY;
        goto Exit;
    }
    memcpy(tmpbuf, buf->base + rec_start + 5, bodylen);
    ptls_clear_memory(buf->base + rec_start, bodylen + 5);
    buf->off = rec_start;

    /* push encrypted records */
    ret = buffer_push_encrypted_records(buf, type, tmpbuf, bodylen, enc);

Exit:
    if (tmpbuf != NULL) {
        ptls_clear_memory(tmpbuf, bodylen);
        free(tmpbuf);
    }
    return ret;
}
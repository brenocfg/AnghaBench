#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {size_t size; TYPE_3__** entries; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_4__ session_ticket_vector_t ;
struct TYPE_15__ {int /*<<< orphan*/ * base; int /*<<< orphan*/  len; } ;
typedef  TYPE_5__ h2o_iovec_t ;
struct TYPE_12__ {scalar_t__ md; int /*<<< orphan*/  key; } ;
struct TYPE_11__ {scalar_t__ cipher; int /*<<< orphan*/  key; } ;
struct TYPE_13__ {scalar_t__ not_before; scalar_t__ not_after; TYPE_2__ hmac; TYPE_1__ cipher; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EVP_CIPHER_key_length (scalar_t__) ; 
 int EVP_MD_block_size (scalar_t__) ; 
 int /*<<< orphan*/  EVP_aes_256_cbc () ; 
 int /*<<< orphan*/  EVP_sha256 () ; 
 scalar_t__ UTC2000 ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_tickets (TYPE_4__*) ; 
 int /*<<< orphan*/  h2o_vector_reserve (int /*<<< orphan*/ *,TYPE_4__*,size_t) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* new_ticket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ok (int) ; 
 int parse_tickets (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_5__ serialize_tickets (TYPE_4__*) ; 

__attribute__((used)) static void test_serialize_tickets(void)
{
    session_ticket_vector_t orig = {NULL}, parsed = {NULL};
    h2o_iovec_t serialized;
    char errstr[256];
    int ret;
    size_t i;

    h2o_vector_reserve(NULL, &orig, orig.size + 2);
    orig.entries[orig.size++] = new_ticket(EVP_aes_256_cbc(), EVP_sha256(), UTC2000, UTC2000 + 3600, 1);
    orig.entries[orig.size++] = new_ticket(EVP_aes_256_cbc(), EVP_sha256(), UTC2000 + 600, UTC2000 + 4200, 1);

    serialized = serialize_tickets(&orig);
    ok(serialized.base != NULL);

    ret = parse_tickets(&parsed, serialized.base, serialized.len, errstr);
    ok(ret == 0);

    ok(parsed.size == orig.size);
    for (i = 0; i != parsed.size; ++i) {
#define OK_VALUE(n) ok(parsed.entries[i]->n == orig.entries[i]->n)
#define OK_MEMCMP(n, s) ok(memcmp(parsed.entries[i]->n, orig.entries[i]->n, (s)) == 0)
        OK_MEMCMP(name, sizeof(parsed.entries[i]->name));
        OK_VALUE(cipher.cipher);
        OK_MEMCMP(cipher.key, EVP_CIPHER_key_length(parsed.entries[i]->cipher.cipher));
        OK_VALUE(hmac.md);
        OK_MEMCMP(hmac.key, EVP_MD_block_size(parsed.entries[i]->hmac.md));
        OK_VALUE(not_before);
        OK_VALUE(not_after);
#undef OK_VALUE
#undef OK_MEMCMP
    }

    free_tickets(&orig);
    free_tickets(&parsed);
    free(serialized.base);
}
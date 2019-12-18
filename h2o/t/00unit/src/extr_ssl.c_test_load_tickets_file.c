#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct st_session_ticket_t {scalar_t__ cipher; scalar_t__ hmac; int not_before; int not_after; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int size; struct st_session_ticket_t** entries; } ;
struct TYPE_3__ {int /*<<< orphan*/  rwlock; TYPE_2__ tickets; } ;

/* Variables and functions */
 scalar_t__ EVP_aes_128_cbc () ; 
 scalar_t__ EVP_aes_256_cbc () ; 
 scalar_t__ EVP_sha1 () ; 
 scalar_t__ EVP_sha256 () ; 
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 struct st_session_ticket_t* find_ticket_for_encryption (TYPE_2__*,int) ; 
 int load_tickets_file (char*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int) ; 
 int /*<<< orphan*/  pthread_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  session_ticket_get_cipher_key (struct st_session_ticket_t*) ; 
 int /*<<< orphan*/  session_ticket_get_hmac_key (struct st_session_ticket_t*) ; 
 TYPE_1__ session_tickets ; 

__attribute__((used)) static void test_load_tickets_file(void)
{
    int ret = load_tickets_file("t/assets/session_tickets.yaml");
    ok(ret == 0);
    if (ret != 0)
        return;

    pthread_rwlock_rdlock(&session_tickets.rwlock);
    ok(session_tickets.tickets.size == 2);
    if (session_tickets.tickets.size != 2)
        goto Exit;

    /* first entry should be the newer one */
    struct st_session_ticket_t *ticket = session_tickets.tickets.entries[0];
    ok(memcmp(ticket->name, H2O_STRLIT("\xe7\xe3\xc6\x98\x0b\x18\x32\xbd\x5d\x23\x91\x75\x72\xe8\x44\x8f")) == 0);
    ok(ticket->cipher == EVP_aes_256_cbc());
    ok(memcmp(session_ticket_get_cipher_key(ticket),
              H2O_STRLIT("\xf6\xe0\x71\xd9\x93\xb0\x5f\x77\xce\x51\xcb\x0f\xe2\xe0\xe1\x8c\x72\x00\xc2\xa7"
                         "\x87\x3a\x66\x00\x8c\x8e\x1d\x75\xae\x7b\x8e\x2a")) == 0);
    ok(ticket->hmac == EVP_sha256());
    ok(memcmp(session_ticket_get_hmac_key(ticket),
              H2O_STRLIT("\xf4\xfc\xb8\x6f\xdf\x03\xa7\xf3\x35\x63\x2e\x66\x8a\x8f\xe9\x56\xc5\xbf\xe7\x7a\x41\x41\x2d\x26\x99"
                         "\x79\x63\x47\x68\x99\x9a\xdd\x6a\x84\xca\xfe\xa4\x1b\x6b\x2c\x47\xaa\xf1\xa5\x14\xca\x9d\x2a\x84\xf4"
                         "\x8d\x1f\x5f\x70\x18\xff\x17\x40\xcf\x9b\x94\x4b\x8f\xcf")) == 0);
    ok(ticket->not_before == 1437093330);
    ok(ticket->not_after == 1437096929);

    /* second is the older one */
    ticket = session_tickets.tickets.entries[1];
    ok(memcmp(ticket->name, H2O_STRLIT("\xa3\x97\xb6\xb7\xfa\xb9\x29\x36\x62\x03\xf1\x6f\xc8\x1f\xfb\xed")) == 0);
    ok(ticket->cipher == EVP_aes_128_cbc());
    ok(memcmp(session_ticket_get_cipher_key(ticket),
              H2O_STRLIT("\xf1\xed\x89\xcd\xe6\x87\x63\x63\x0e\x80\xd2\xbe\x82\x7c\xfb\x98")) == 0);
    ok(ticket->hmac == EVP_sha1());
    ok(memcmp(session_ticket_get_hmac_key(ticket),
              H2O_STRLIT("\xe3\xfe\x72\x64\x4f\x64\x31\x5a\x4a\x8a\xd6\x37\x69\xa3\x57\x7c\xce\xc4\xdd\x13\xb2\x0e\xaf\x8c\x00\x88"
                         "\x86\xe5\x45\x8d\xb1\x0e\x65\x8c\xf2\xa8\x3f\x04\x40\x3a\xc4\xe9\x80\x35\xd2\x42\x2a\x75\x80\x67\x30\xeb"
                         "\x4f\x2f\xee\x12\xfa\xff\x95\x48\x95\xbc\x65\xd1")) == 0);
    ok(ticket->not_before == 1437092430);
    ok(ticket->not_after == 1437096029);

    ticket = find_ticket_for_encryption(&session_tickets.tickets, 1437092429);
    ok(ticket == NULL);
    ticket = find_ticket_for_encryption(&session_tickets.tickets, 1437092430);
    ok(ticket == session_tickets.tickets.entries[1]);
    ticket = find_ticket_for_encryption(&session_tickets.tickets, 1437093329);
    ok(ticket == session_tickets.tickets.entries[1]);
    ticket = find_ticket_for_encryption(&session_tickets.tickets, 1437093330);
    ok(ticket == session_tickets.tickets.entries[0]);
    ticket = find_ticket_for_encryption(&session_tickets.tickets, 1437096029);
    ok(ticket == session_tickets.tickets.entries[0]);
    ticket = find_ticket_for_encryption(&session_tickets.tickets, 1437096030);
    ok(ticket == session_tickets.tickets.entries[0]);
    ticket = find_ticket_for_encryption(&session_tickets.tickets, 1437096929);
    ok(ticket == session_tickets.tickets.entries[0]);
    ticket = find_ticket_for_encryption(&session_tickets.tickets, 1437096930);
    ok(ticket == NULL);

Exit:
    pthread_rwlock_unlock(&session_tickets.rwlock);
    ;
}
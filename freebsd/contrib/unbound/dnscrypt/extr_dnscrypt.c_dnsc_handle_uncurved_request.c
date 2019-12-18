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
struct comm_reply {int /*<<< orphan*/  max_udp_size; TYPE_1__* c; int /*<<< orphan*/  nmkey; int /*<<< orphan*/  client_nonce; int /*<<< orphan*/  dnsc_cert; int /*<<< orphan*/  is_dnscrypted; } ;
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  dnscrypt_buffer; int /*<<< orphan*/  buffer; int /*<<< orphan*/  dnscrypt; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  comm_point_drop_reply (struct comm_reply*) ; 
 scalar_t__ comm_udp ; 
 scalar_t__ dnscrypt_server_curve (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

int
dnsc_handle_uncurved_request(struct comm_reply *repinfo)
{
    if(!repinfo->c->dnscrypt) {
        return 1;
    }
    sldns_buffer_copy(repinfo->c->dnscrypt_buffer, repinfo->c->buffer);
    if(!repinfo->is_dnscrypted) {
        return 1;
    }
	if(dnscrypt_server_curve(repinfo->dnsc_cert,
                             repinfo->client_nonce,
                             repinfo->nmkey,
                             repinfo->c->dnscrypt_buffer,
                             repinfo->c->type == comm_udp,
                             repinfo->max_udp_size) != 0){
		verbose(VERB_ALGO, "dnscrypt: Failed to curve cached missed answer");
		comm_point_drop_reply(repinfo);
		return 0;
	}
    return 1;
}
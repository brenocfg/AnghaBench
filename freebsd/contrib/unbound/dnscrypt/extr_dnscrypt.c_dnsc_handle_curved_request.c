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
struct dnsc_env {int dummy; } ;
struct comm_reply {int is_dnscrypted; int /*<<< orphan*/  nmkey; int /*<<< orphan*/  client_nonce; int /*<<< orphan*/ * dnsc_cert; struct comm_point* c; } ;
struct comm_point {int /*<<< orphan*/  buffer; int /*<<< orphan*/  dnscrypt; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  comm_point_drop_reply (struct comm_reply*) ; 
 int /*<<< orphan*/ * dnsc_find_cert (struct dnsc_env*,int /*<<< orphan*/ ) ; 
 scalar_t__ dnscrypt_server_uncurve (struct dnsc_env*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_rewind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

int
dnsc_handle_curved_request(struct dnsc_env* dnscenv,
                           struct comm_reply* repinfo)
{
    struct comm_point* c = repinfo->c;

    repinfo->is_dnscrypted = 0;
    if( !c->dnscrypt ) {
        return 1;
    }
    // Attempt to decrypt the query. If it is not crypted, we may still need
    // to serve the certificate.
    verbose(VERB_ALGO, "handle request called on DNSCrypt socket");
    if ((repinfo->dnsc_cert = dnsc_find_cert(dnscenv, c->buffer)) != NULL) {
        if(dnscrypt_server_uncurve(dnscenv,
                                   repinfo->dnsc_cert,
                                   repinfo->client_nonce,
                                   repinfo->nmkey,
                                   c->buffer) != 0){
            verbose(VERB_ALGO, "dnscrypt: Failed to uncurve");
            comm_point_drop_reply(repinfo);
            return 0;
        }
        repinfo->is_dnscrypted = 1;
        sldns_buffer_rewind(c->buffer);
    }
    return 1;
}
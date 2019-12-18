#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_7__ {scalar_t__ early_data; } ;
struct TYPE_10__ {scalar_t__ recv_max_early_data; scalar_t__ early_data_count; TYPE_1__ ext; int /*<<< orphan*/  server; TYPE_3__* psksession; TYPE_3__* session; } ;
struct TYPE_8__ {scalar_t__ max_early_data; } ;
struct TYPE_9__ {TYPE_2__ ext; } ;
typedef  TYPE_3__ SSL_SESSION ;
typedef  TYPE_4__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_UNEXPECTED_MESSAGE ; 
 scalar_t__ SSL_EARLY_DATA_ACCEPTED ; 
 int /*<<< orphan*/  SSL_F_EARLY_DATA_COUNT_OK ; 
 int /*<<< orphan*/  SSL_R_TOO_MUCH_EARLY_DATA ; 
 int /*<<< orphan*/  SSLfatal (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 

int early_data_count_ok(SSL *s, size_t length, size_t overhead, int send)
{
    uint32_t max_early_data;
    SSL_SESSION *sess = s->session;

    /*
     * If we are a client then we always use the max_early_data from the
     * session/psksession. Otherwise we go with the lowest out of the max early
     * data set in the session and the configured max_early_data.
     */
    if (!s->server && sess->ext.max_early_data == 0) {
        if (!ossl_assert(s->psksession != NULL
                         && s->psksession->ext.max_early_data > 0)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_EARLY_DATA_COUNT_OK,
                     ERR_R_INTERNAL_ERROR);
            return 0;
        }
        sess = s->psksession;
    }

    if (!s->server)
        max_early_data = sess->ext.max_early_data;
    else if (s->ext.early_data != SSL_EARLY_DATA_ACCEPTED)
        max_early_data = s->recv_max_early_data;
    else
        max_early_data = s->recv_max_early_data < sess->ext.max_early_data
                         ? s->recv_max_early_data : sess->ext.max_early_data;

    if (max_early_data == 0) {
        SSLfatal(s, send ? SSL_AD_INTERNAL_ERROR : SSL_AD_UNEXPECTED_MESSAGE,
                 SSL_F_EARLY_DATA_COUNT_OK, SSL_R_TOO_MUCH_EARLY_DATA);
        return 0;
    }

    /* If we are dealing with ciphertext we need to allow for the overhead */
    max_early_data += overhead;

    if (s->early_data_count + length > max_early_data) {
        SSLfatal(s, send ? SSL_AD_INTERNAL_ERROR : SSL_AD_UNEXPECTED_MESSAGE,
                 SSL_F_EARLY_DATA_COUNT_OK, SSL_R_TOO_MUCH_EARLY_DATA);
        return 0;
    }
    s->early_data_count += length;

    return 1;
}
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
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_4__ {scalar_t__ early_data_state; } ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 scalar_t__ SSL_EARLY_DATA_FINISHED_WRITING ; 
 scalar_t__ SSL_EARLY_DATA_WRITE_RETRY ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_END_OF_EARLY_DATA ; 
 int /*<<< orphan*/  SSLfatal (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tls_construct_end_of_early_data(SSL *s, WPACKET *pkt)
{
    if (s->early_data_state != SSL_EARLY_DATA_WRITE_RETRY
            && s->early_data_state != SSL_EARLY_DATA_FINISHED_WRITING) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_TLS_CONSTRUCT_END_OF_EARLY_DATA,
                 ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED);
        return 0;
    }

    s->early_data_state = SSL_EARLY_DATA_FINISHED_WRITING;
    return 1;
}
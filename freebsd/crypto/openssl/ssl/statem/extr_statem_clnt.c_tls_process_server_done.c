#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_3__* s3; } ;
struct TYPE_10__ {TYPE_1__* new_cipher; } ;
struct TYPE_11__ {TYPE_2__ tmp; } ;
struct TYPE_9__ {int algorithm_mkey; } ;
typedef  TYPE_4__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;
typedef  int /*<<< orphan*/  MSG_PROCESS_RETURN ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_PROCESS_ERROR ; 
 int /*<<< orphan*/  MSG_PROCESS_FINISHED_READING ; 
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 scalar_t__ SRP_Calc_A_param (TYPE_4__*) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_PROCESS_SERVER_DONE ; 
 int /*<<< orphan*/  SSL_R_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  SSL_R_SRP_A_CALC ; 
 int SSL_kSRP ; 
 int /*<<< orphan*/  SSLfatal (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_process_initial_server_flight (TYPE_4__*) ; 

MSG_PROCESS_RETURN tls_process_server_done(SSL *s, PACKET *pkt)
{
    if (PACKET_remaining(pkt) > 0) {
        /* should contain no data */
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_SERVER_DONE,
                 SSL_R_LENGTH_MISMATCH);
        return MSG_PROCESS_ERROR;
    }
#ifndef OPENSSL_NO_SRP
    if (s->s3->tmp.new_cipher->algorithm_mkey & SSL_kSRP) {
        if (SRP_Calc_A_param(s) <= 0) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_SERVER_DONE,
                     SSL_R_SRP_A_CALC);
            return MSG_PROCESS_ERROR;
        }
    }
#endif

    if (!tls_process_initial_server_flight(s)) {
        /* SSLfatal() already called */
        return MSG_PROCESS_ERROR;
    }

    return MSG_PROCESS_FINISHED_READING;
}
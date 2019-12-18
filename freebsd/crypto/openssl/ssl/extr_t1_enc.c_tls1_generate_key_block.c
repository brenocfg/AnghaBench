#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* session; TYPE_1__* s3; } ;
struct TYPE_7__ {int /*<<< orphan*/  master_key_length; int /*<<< orphan*/  master_key; } ;
struct TYPE_6__ {int /*<<< orphan*/  client_random; int /*<<< orphan*/  server_random; } ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL3_RANDOM_SIZE ; 
 int /*<<< orphan*/  TLS_MD_KEY_EXPANSION_CONST ; 
 int /*<<< orphan*/  TLS_MD_KEY_EXPANSION_CONST_SIZE ; 
 int tls1_PRF (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t,int) ; 

__attribute__((used)) static int tls1_generate_key_block(SSL *s, unsigned char *km, size_t num)
{
    int ret;

    /* Calls SSLfatal() as required */
    ret = tls1_PRF(s,
                   TLS_MD_KEY_EXPANSION_CONST,
                   TLS_MD_KEY_EXPANSION_CONST_SIZE, s->s3->server_random,
                   SSL3_RANDOM_SIZE, s->s3->client_random, SSL3_RANDOM_SIZE,
                   NULL, 0, NULL, 0, s->session->master_key,
                   s->session->master_key_length, km, num, 1);

    return ret;
}
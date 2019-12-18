#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  compress; } ;
struct TYPE_5__ {int length; int /*<<< orphan*/  data; int /*<<< orphan*/  input; } ;
typedef  TYPE_1__ SSL3_RECORD ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int COMP_compress_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ SSL3_RT_MAX_COMPRESSED_OVERHEAD ; 

int ssl3_do_compress(SSL *ssl, SSL3_RECORD *wr)
{
#ifndef OPENSSL_NO_COMP
    int i;

    /* TODO(size_t): Convert this call */
    i = COMP_compress_block(ssl->compress, wr->data,
                            (int)(wr->length + SSL3_RT_MAX_COMPRESSED_OVERHEAD),
                            wr->input, (int)wr->length);
    if (i < 0)
        return 0;
    else
        wr->length = i;

    wr->input = wr->data;
#endif
    return 1;
}
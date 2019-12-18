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
struct TYPE_2__ {unsigned char* data; unsigned int len; } ;
typedef  TYPE_1__ tlsextnextprotoctx ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int SSL_TLSEXT_ERR_OK ; 

__attribute__((used)) static int next_proto_cb(SSL *s, const unsigned char **data,
                         unsigned int *len, void *arg)
{
    tlsextnextprotoctx *next_proto = arg;

    *data = next_proto->data;
    *len = next_proto->len;

    return SSL_TLSEXT_ERR_OK;
}
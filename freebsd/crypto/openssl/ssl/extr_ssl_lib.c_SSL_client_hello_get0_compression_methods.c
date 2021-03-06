#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* clienthello; } ;
struct TYPE_4__ {unsigned char* compressions; size_t compressions_len; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */

size_t SSL_client_hello_get0_compression_methods(SSL *s, const unsigned char **out)
{
    if (s->clienthello == NULL)
        return 0;
    if (out != NULL)
        *out = s->clienthello->compressions;
    return s->clienthello->compressions_len;
}
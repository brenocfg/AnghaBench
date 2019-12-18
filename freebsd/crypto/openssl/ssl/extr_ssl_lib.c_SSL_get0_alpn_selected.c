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
struct TYPE_5__ {TYPE_1__* s3; } ;
struct TYPE_4__ {unsigned char* alpn_selected; scalar_t__ alpn_selected_len; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */

void SSL_get0_alpn_selected(const SSL *ssl, const unsigned char **data,
                            unsigned int *len)
{
    *data = NULL;
    if (ssl->s3)
        *data = ssl->s3->alpn_selected;
    if (*data == NULL)
        *len = 0;
    else
        *len = (unsigned int)ssl->s3->alpn_selected_len;
}
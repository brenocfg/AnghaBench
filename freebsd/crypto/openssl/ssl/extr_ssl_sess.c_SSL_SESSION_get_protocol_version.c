#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ssl_version; } ;
typedef  TYPE_1__ SSL_SESSION ;

/* Variables and functions */

int SSL_SESSION_get_protocol_version(const SSL_SESSION *s)
{
    return s->ssl_version;
}
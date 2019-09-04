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
typedef  scalar_t__ uint16_t ;
struct TYPE_5__ {TYPE_1__* ssl; } ;
typedef  TYPE_2__ h2o_socket_t ;
struct TYPE_4__ {scalar_t__ record_overhead; } ;

/* Variables and functions */

__attribute__((used)) static uint16_t calc_suggested_tls_payload_size(h2o_socket_t *sock, uint16_t suggested_tls_record_size)
{
    uint16_t ps = suggested_tls_record_size;
    if (sock->ssl != NULL && sock->ssl->record_overhead < ps)
        ps -= sock->ssl->record_overhead;
    return ps;
}
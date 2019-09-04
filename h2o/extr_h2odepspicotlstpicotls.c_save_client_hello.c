#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ptls_t ;
typedef  int /*<<< orphan*/  ptls_on_client_hello_t ;
struct TYPE_8__ {scalar_t__ count; TYPE_1__* list; } ;
struct TYPE_7__ {int /*<<< orphan*/  len; scalar_t__ base; } ;
struct TYPE_9__ {scalar_t__ esni; TYPE_3__ negotiated_protocols; TYPE_2__ server_name; } ;
typedef  TYPE_4__ ptls_on_client_hello_parameters_t ;
struct TYPE_6__ {int /*<<< orphan*/  len; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ptls_set_negotiated_protocol (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptls_set_server_name (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  was_esni ; 

__attribute__((used)) static int save_client_hello(ptls_on_client_hello_t *self, ptls_t *tls, ptls_on_client_hello_parameters_t *params)
{
    ptls_set_server_name(tls, (const char *)params->server_name.base, params->server_name.len);
    if (params->negotiated_protocols.count != 0)
        ptls_set_negotiated_protocol(tls, (const char *)params->negotiated_protocols.list[0].base,
                                     params->negotiated_protocols.list[0].len);
    if (params->esni)
        ++was_esni;
    return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ptls_t ;

/* Variables and functions */
 int PTLS_ALERT_ILLEGAL_PARAMETER ; 
 int handle_certificate (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int*) ; 

__attribute__((used)) static int client_do_handle_certificate(ptls_t *tls, const uint8_t *src, const uint8_t *end)
{
    int got_certs, ret;

    if ((ret = handle_certificate(tls, src, end, &got_certs)) != 0)
        return ret;
    if (!got_certs)
        return PTLS_ALERT_ILLEGAL_PARAMETER;

    return 0;
}
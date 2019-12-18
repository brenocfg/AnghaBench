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
 int PTLS_ALERT_DECODE_ERROR ; 
 int PTLS_ALERT_TO_PEER_ERROR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_alert(ptls_t *tls, const uint8_t *src, size_t len)
{
    if (len != 2)
        return PTLS_ALERT_DECODE_ERROR;

    uint8_t desc = src[1];

    /* all fatal alerts and USER_CANCELLED warning tears down the connection immediately, regardless of the transmitted level */
    return PTLS_ALERT_TO_PEER_ERROR(desc);
}
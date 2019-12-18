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
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL3_RT_HANDSHAKE ; 
 int ssl3_do_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ssl3_handshake_write(SSL *s)
{
    return ssl3_do_write(s, SSL3_RT_HANDSHAKE);
}
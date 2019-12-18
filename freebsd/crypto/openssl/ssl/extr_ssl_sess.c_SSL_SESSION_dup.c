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
typedef  int /*<<< orphan*/  SSL_SESSION ;

/* Variables and functions */
 int /*<<< orphan*/ * ssl_session_dup (int /*<<< orphan*/ *,int) ; 

SSL_SESSION *SSL_SESSION_dup(SSL_SESSION *src)
{
    return ssl_session_dup(src, 1);
}
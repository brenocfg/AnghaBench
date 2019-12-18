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
 int verify_cookie_callback (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

int verify_stateless_cookie_callback(SSL *ssl, const unsigned char *cookie,
                                     size_t cookie_len)
{
    return verify_cookie_callback(ssl, cookie, cookie_len);
}
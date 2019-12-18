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
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  ssl_get_algorithm2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* ssl_md (int /*<<< orphan*/ ) ; 

const EVP_MD *ssl_handshake_md(SSL *s)
{
    return ssl_md(ssl_get_algorithm2(s));
}
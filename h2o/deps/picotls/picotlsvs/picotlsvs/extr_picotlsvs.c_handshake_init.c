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
typedef  int /*<<< orphan*/  ptls_t ;
typedef  int /*<<< orphan*/  ptls_handshake_properties_t ;
typedef  int /*<<< orphan*/  ptls_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  ptls_buffer_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int ptls_handshake (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int handshake_init(ptls_t * tls, ptls_buffer_t * sendbuf, ptls_handshake_properties_t * ph_prop)
{
    size_t inlen = 0, roff = 0;

    ptls_buffer_init(sendbuf, "", 0);
    int ret = ptls_handshake(tls, sendbuf, NULL, NULL, ph_prop);

    return ret;
}
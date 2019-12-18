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
typedef  int /*<<< orphan*/  SSL_CERT_LOOKUP ;

/* Variables and functions */
 size_t OSSL_NELEM (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* ssl_cert_info ; 

const SSL_CERT_LOOKUP *ssl_cert_lookup_by_idx(size_t idx)
{
    if (idx >= OSSL_NELEM(ssl_cert_info))
        return NULL;
    return &ssl_cert_info[idx];
}
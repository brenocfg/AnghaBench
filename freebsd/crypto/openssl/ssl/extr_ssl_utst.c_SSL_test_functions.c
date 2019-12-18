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
struct openssl_ssl_test_functions {int dummy; } ;

/* Variables and functions */
 struct openssl_ssl_test_functions const ssl_test_functions ; 

const struct openssl_ssl_test_functions *SSL_test_functions(void)
{
    return &ssl_test_functions;
}
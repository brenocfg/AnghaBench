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
struct tls_global {int check_crl; } ;

/* Variables and functions */

int tls_global_set_verify(void *tls_ctx, int check_crl, int strict)
{
	struct tls_global *global = tls_ctx;
	global->check_crl = check_crl;
	return 0;
}
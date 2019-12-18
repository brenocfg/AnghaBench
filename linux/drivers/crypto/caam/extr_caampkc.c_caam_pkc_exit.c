#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  akcipher; scalar_t__ registered; } ;

/* Variables and functions */
 TYPE_1__ caam_rsa ; 
 int /*<<< orphan*/  crypto_unregister_akcipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_done ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zero_buffer ; 

void caam_pkc_exit(void)
{
	if (!init_done)
		return;

	if (caam_rsa.registered)
		crypto_unregister_akcipher(&caam_rsa.akcipher);

	kfree(zero_buffer);
}
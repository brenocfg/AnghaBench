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

/* Variables and functions */
 int /*<<< orphan*/  crypto_unregister_acomp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hisi_zip_acomp_gzip ; 
 int /*<<< orphan*/  hisi_zip_acomp_zlib ; 

void hisi_zip_unregister_from_crypto(void)
{
	crypto_unregister_acomp(&hisi_zip_acomp_gzip);
	crypto_unregister_acomp(&hisi_zip_acomp_zlib);
}
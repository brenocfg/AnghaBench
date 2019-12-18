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
 int /*<<< orphan*/  crypto_unregister_akcipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_template (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsa ; 
 int /*<<< orphan*/  rsa_pkcs1pad_tmpl ; 

__attribute__((used)) static void rsa_exit(void)
{
	crypto_unregister_template(&rsa_pkcs1pad_tmpl);
	crypto_unregister_akcipher(&rsa);
}
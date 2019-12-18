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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ifxdeu_fini_aes () ; 
 int /*<<< orphan*/  ifxdeu_fini_arc4 () ; 
 int /*<<< orphan*/  ifxdeu_fini_des () ; 
 int /*<<< orphan*/  ifxdeu_fini_md5 () ; 
 int /*<<< orphan*/  ifxdeu_fini_md5_hmac () ; 
 int /*<<< orphan*/  ifxdeu_fini_sha1 () ; 
 int /*<<< orphan*/  ifxdeu_fini_sha1_hmac () ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int ltq_deu_remove(struct platform_device *pdev)
{
//#ifdef CONFIG_CRYPTO_DEV_PWR_SAVE_MODE
    #if defined(CONFIG_CRYPTO_DEV_DES)
    ifxdeu_fini_des ();
    #endif
    #if defined(CONFIG_CRYPTO_DEV_AES)
    ifxdeu_fini_aes ();
    #endif
    #if defined(CONFIG_CRYPTO_DEV_ARC4)
    ifxdeu_fini_arc4 ();
    #endif
    #if defined(CONFIG_CRYPTO_DEV_SHA1)
    ifxdeu_fini_sha1 ();
    #endif
    #if defined(CONFIG_CRYPTO_DEV_MD5)
    ifxdeu_fini_md5 ();
    #endif
    #if defined(CONFIG_CRYPTO_DEV_SHA1_HMAC)
    ifxdeu_fini_sha1_hmac ();
    #endif
    #if defined(CONFIG_CRYPTO_DEV_MD5_HMAC)
    ifxdeu_fini_md5_hmac ();
    #endif
    printk("DEU has exited successfully\n");

	return 0;
}
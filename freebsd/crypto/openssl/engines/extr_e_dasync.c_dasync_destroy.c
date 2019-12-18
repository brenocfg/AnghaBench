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
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_unload_DASYNC_strings () ; 
 int /*<<< orphan*/  RSA_meth_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasync_rsa_method ; 
 int /*<<< orphan*/  destroy_ciphers () ; 
 int /*<<< orphan*/  destroy_digests () ; 

__attribute__((used)) static int dasync_destroy(ENGINE *e)
{
    destroy_digests();
    destroy_ciphers();
    RSA_meth_free(dasync_rsa_method);
    ERR_unload_DASYNC_strings();
    return 1;
}
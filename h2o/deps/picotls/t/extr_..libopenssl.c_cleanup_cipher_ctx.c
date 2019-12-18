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
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_CIPHER_CTX_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void cleanup_cipher_ctx(EVP_CIPHER_CTX *ctx)
{
    if (!EVP_CIPHER_CTX_cleanup(ctx)) {
        fprintf(stderr, "EVP_CIPHER_CTX_cleanup() failed\n");
        abort();
    }
}
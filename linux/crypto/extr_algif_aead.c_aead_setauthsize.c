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
struct aead_tfm {int /*<<< orphan*/  aead; } ;

/* Variables and functions */
 int crypto_aead_setauthsize (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int aead_setauthsize(void *private, unsigned int authsize)
{
	struct aead_tfm *tfm = private;

	return crypto_aead_setauthsize(tfm->aead, authsize);
}
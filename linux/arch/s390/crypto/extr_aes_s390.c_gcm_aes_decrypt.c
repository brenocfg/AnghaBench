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
struct aead_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPACF_DECRYPT ; 
 int gcm_aes_crypt (struct aead_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gcm_aes_decrypt(struct aead_request *req)
{
	return gcm_aes_crypt(req, CPACF_DECRYPT);
}
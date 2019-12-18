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
 int /*<<< orphan*/  AES_FLAGS_ENCRYPT ; 
 int mtk_aes_gcm_crypt (struct aead_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_aes_gcm_encrypt(struct aead_request *req)
{
	return mtk_aes_gcm_crypt(req, AES_FLAGS_ENCRYPT);
}
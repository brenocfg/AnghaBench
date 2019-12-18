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
struct skcipher_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_IV_SIZE ; 
 int crypto4xx_crypt (struct skcipher_request*,int /*<<< orphan*/ ,int,int) ; 

int crypto4xx_encrypt_iv_block(struct skcipher_request *req)
{
	return crypto4xx_crypt(req, AES_IV_SIZE, false, true);
}
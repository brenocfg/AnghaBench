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
struct ablkcipher_request {int dummy; } ;

/* Variables and functions */
 int AES_FLAGS_CFB8 ; 
 int AES_FLAGS_ENCRYPT ; 
 int atmel_aes_crypt (struct ablkcipher_request*,int) ; 

__attribute__((used)) static int atmel_aes_cfb8_encrypt(struct ablkcipher_request *req)
{
	return atmel_aes_crypt(req, AES_FLAGS_CFB8 | AES_FLAGS_ENCRYPT);
}
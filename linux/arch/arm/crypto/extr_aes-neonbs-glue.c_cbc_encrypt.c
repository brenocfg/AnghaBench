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
 int /*<<< orphan*/  cbc_encrypt_one ; 
 int crypto_cbc_encrypt_walk (struct skcipher_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cbc_encrypt(struct skcipher_request *req)
{
	return crypto_cbc_encrypt_walk(req, cbc_encrypt_one);
}
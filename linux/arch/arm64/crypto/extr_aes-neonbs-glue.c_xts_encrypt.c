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
 int __xts_crypt (struct skcipher_request*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aesbs_xts_encrypt ; 

__attribute__((used)) static int xts_encrypt(struct skcipher_request *req)
{
	return __xts_crypt(req, true, aesbs_xts_encrypt);
}
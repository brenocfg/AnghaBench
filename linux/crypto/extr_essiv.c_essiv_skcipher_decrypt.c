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
 int essiv_skcipher_crypt (struct skcipher_request*,int) ; 

__attribute__((used)) static int essiv_skcipher_decrypt(struct skcipher_request *req)
{
	return essiv_skcipher_crypt(req, false);
}
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
typedef  int /*<<< orphan*/  des_key_schedule ;
typedef  int /*<<< orphan*/  DES_LONG ;

/* Variables and functions */
 int /*<<< orphan*/  c2l (unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  des_decrypt3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  des_encrypt3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2c (int /*<<< orphan*/ ,unsigned char*) ; 

void des_ecb3_encrypt(unsigned char *input, unsigned char *output,
             des_key_schedule ks1, des_key_schedule ks2, des_key_schedule ks3,
             int enc)
{
	register DES_LONG l0,l1;
	DES_LONG ll[2];
	const unsigned char *in = input;
	unsigned char *out = output;
 
	c2l(in,l0); 
	c2l(in,l1);
	ll[0]=l0; 
	ll[1]=l1;

	if (enc)
		des_encrypt3(ll,ks1,ks2,ks3);
	else
		des_decrypt3(ll,ks1,ks2,ks3);

	l0=ll[0];
	l1=ll[1];
	l2c(l0,out);
	l2c(l1,out);
}
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
 int /*<<< orphan*/  DES_DECRYPT ; 
 int /*<<< orphan*/  DES_ENCRYPT ; 
 int /*<<< orphan*/  FP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  des_encrypt2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void des_decrypt3(DES_LONG *data, des_key_schedule ks1, des_key_schedule ks2,
	     des_key_schedule ks3)
{
	DES_LONG l,r;

	l=data[0];
	r=data[1];
	IP(l,r);
	data[0]=l;
	data[1]=r;
	des_encrypt2((DES_LONG *)data,ks3,DES_DECRYPT);
	des_encrypt2((DES_LONG *)data,ks2,DES_ENCRYPT);
	des_encrypt2((DES_LONG *)data,ks1,DES_DECRYPT);
	l=data[0];
	r=data[1];
	FP(r,l);
	data[0]=l;
	data[1]=r;
}
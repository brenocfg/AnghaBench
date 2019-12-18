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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  seed ;
typedef  int /*<<< orphan*/  MINT ;

/* Variables and functions */
 unsigned short BASE ; 
 int BASEBITS ; 
 int /*<<< orphan*/  HEXMODULUS ; 
 int KEYSIZE ; 
 short PROOT ; 
 int /*<<< orphan*/  adjust (char*,char*) ; 
 int /*<<< orphan*/  getseed (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mp_itom (short) ; 
 int /*<<< orphan*/  mp_madd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_mdiv (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_mfree (int /*<<< orphan*/ *) ; 
 char* mp_mtox (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_mult (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_pow (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mp_xtom (int /*<<< orphan*/ ) ; 

void
genkeys(char *public, char *secret, char *pass)
{
	unsigned int i;

#   define BASEBITS (8*sizeof (short) - 1)
#	define BASE		(1 << BASEBITS)

	MINT *pk = mp_itom(0);
	MINT *sk = mp_itom(0);
	MINT *tmp;
	MINT *base = mp_itom((short)BASE);
	MINT *root = mp_itom(PROOT);
	MINT *modulus = mp_xtom(HEXMODULUS);
	short r;
	unsigned short seed[KEYSIZE/BASEBITS + 1];
	char *xkey;

	getseed((char *)seed, sizeof (seed), (u_char *)pass);
	for (i = 0; i < KEYSIZE/BASEBITS + 1; i++) {
		r = seed[i] % BASE;
		tmp = mp_itom(r);
		mp_mult(sk, base, sk);
		mp_madd(sk, tmp, sk);
		mp_mfree(tmp);
	}
	tmp = mp_itom(0);
	mp_mdiv(sk, modulus, tmp, sk);
	mp_mfree(tmp);
	mp_pow(root, sk, modulus, pk);
	xkey = mp_mtox(sk);
	adjust(secret, xkey);
	xkey = mp_mtox(pk);
	adjust(public, xkey);
	mp_mfree(sk);
	mp_mfree(base);
	mp_mfree(pk);
	mp_mfree(root);
	mp_mfree(modulus);
}
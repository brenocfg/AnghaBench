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
typedef  int /*<<< orphan*/  MINT ;
typedef  int /*<<< orphan*/  IdeaData ;
typedef  int /*<<< orphan*/  DesData ;

/* Variables and functions */
 int /*<<< orphan*/  DES_set_odd_parity (int /*<<< orphan*/ *) ; 
 char* HEXMODULUS ; 
 int /*<<< orphan*/  extractdeskey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extractideakey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mp_itom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_mfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_pow (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mp_xtom (char*) ; 

void
common_key(char *xsecret, char *xpublic, IdeaData *ideakey, DesData *deskey)
{
        MINT *public;
        MINT *secret;
        MINT *common;
	MINT *modulus = mp_xtom(HEXMODULUS);

        public = mp_xtom(xpublic);
        secret = mp_xtom(xsecret);
        common = mp_itom(0);
        mp_pow(public, secret, modulus, common);
        extractdeskey(common, deskey);
        extractideakey(common, ideakey);
	DES_set_odd_parity(deskey);
        mp_mfree(common);
        mp_mfree(secret);
        mp_mfree(public);
	mp_mfree(modulus);
}
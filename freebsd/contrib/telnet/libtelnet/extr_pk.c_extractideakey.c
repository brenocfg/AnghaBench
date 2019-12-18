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

/* Variables and functions */
 int KEYSIZE ; 
 int /*<<< orphan*/ * mp_itom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_madd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_mfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_sdiv (int /*<<< orphan*/ *,short,int /*<<< orphan*/ *,short*) ; 

__attribute__((used)) static void
extractideakey(MINT *ck, IdeaData *ideakey)
{
        MINT *a;
        MINT *z;
        short r;
        int i;
        short base = (1 << 8);
        char *k;

        z = mp_itom(0);
        a = mp_itom(0);
        mp_madd(ck, z, a);
        for (i = 0; i < ((KEYSIZE - 128) / 8); i++) {
                mp_sdiv(a, base, a, &r);
        }
        k = (char *)ideakey;
        for (i = 0; i < 16; i++) {
                mp_sdiv(a, base, a, &r);
                *k++ = r;
        }
	mp_mfree(z);
        mp_mfree(a);
}
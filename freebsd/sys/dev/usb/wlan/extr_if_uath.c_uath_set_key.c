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
struct uath_softc {int dummy; } ;
struct uath_cmd_crypto {void* flags; int* key; struct uath_cmd_crypto* magic2; void* mask; void* size; void* magic1; void* keyidx; } ;
struct ieee80211_key {int wk_keylen; int* wk_key; } ;
typedef  int /*<<< orphan*/  crypto ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct uath_softc*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  UATH_DEBUG_CRYPTO ; 
 int UATH_DEFAULT_KEY ; 
 int /*<<< orphan*/  WDCMSG_SET_KEY_CACHE_ENTRY ; 
 void* htobe32 (int) ; 
 int /*<<< orphan*/  memset (struct uath_cmd_crypto*,int,int) ; 
 int uath_cmd_write (struct uath_softc*,int /*<<< orphan*/ ,struct uath_cmd_crypto*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uath_set_key(struct uath_softc *sc, const struct ieee80211_key *wk,
    int index)
{
#if 0
	struct uath_cmd_crypto crypto;
	int i;

	memset(&crypto, 0, sizeof(crypto));
	crypto.keyidx = htobe32(index);
	crypto.magic1 = htobe32(1);
	crypto.size   = htobe32(368);
	crypto.mask   = htobe32(0xffff);
	crypto.flags  = htobe32(0x80000068);
	if (index != UATH_DEFAULT_KEY)
		crypto.flags |= htobe32(index << 16);
	memset(crypto.magic2, 0xff, sizeof(crypto.magic2));

	/*
	 * Each byte of the key must be XOR'ed with 10101010 before being
	 * transmitted to the firmware.
	 */
	for (i = 0; i < wk->wk_keylen; i++)
		crypto.key[i] = wk->wk_key[i] ^ 0xaa;

	DPRINTF(sc, UATH_DEBUG_CRYPTO,
	    "setting crypto key index=%d len=%d\n", index, wk->wk_keylen);
	return uath_cmd_write(sc, WDCMSG_SET_KEY_CACHE_ENTRY, &crypto,
	    sizeof crypto, 0);
#else
	/* XXX support H/W cryto  */
	return (0);
#endif
}
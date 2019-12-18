#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  size_t u_char ;
struct TYPE_2__ {size_t* salt; size_t* mkey; } ;
struct g_bde_softc {TYPE_1__ key; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  keyInstance ;
typedef  size_t MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  AES_makekey (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  G_BDE_KKEYBITS ; 
 int /*<<< orphan*/  MD5Final (size_t*,size_t*) ; 
 int /*<<< orphan*/  MD5Init (size_t*) ; 
 int /*<<< orphan*/  MD5Update (size_t*,size_t*,int) ; 
 int /*<<< orphan*/  bzero (size_t*,int) ; 
 int /*<<< orphan*/  le64enc (size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_bde_kkey(struct g_bde_softc *sc, keyInstance *ki, int dir, off_t sector)
{
	u_int t;
	MD5_CTX ct;
	u_char buf[16];
	u_char buf2[8];

	/* We have to be architecture neutral */
	le64enc(buf2, sector);

	MD5Init(&ct);
	MD5Update(&ct, sc->key.salt, 8);
	MD5Update(&ct, buf2, sizeof buf2);
	MD5Update(&ct, sc->key.salt + 8, 8);
	MD5Final(buf, &ct);

	MD5Init(&ct);
	for (t = 0; t < 16; t++) {
		MD5Update(&ct, &sc->key.mkey[buf[t]], 1);
		if (t == 8)
			MD5Update(&ct, buf2, sizeof buf2);
	}
	bzero(buf2, sizeof buf2);
	MD5Final(buf, &ct);
	bzero(&ct, sizeof ct);
	AES_makekey(ki, dir, G_BDE_KKEYBITS, buf);
	bzero(buf, sizeof buf);
}
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
typedef  int /*<<< orphan*/  u_char ;
struct g_bde_work {scalar_t__ length; int ko; scalar_t__ offset; scalar_t__ data; TYPE_1__* ksp; struct g_bde_softc* softc; } ;
struct g_bde_softc {int sectorsize; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  keyInstance ;
typedef  int /*<<< orphan*/  cipherInstance ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_decrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  AES_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AES_makekey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DIR_DECRYPT ; 
 int /*<<< orphan*/  G_BDE_SKEYBITS ; 
 int G_BDE_SKEYLEN ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  g_bde_kkey (struct g_bde_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

void
g_bde_crypt_read(struct g_bde_work *wp)
{
	struct g_bde_softc *sc;
	u_char *d;
	u_int n;
	off_t o;
	u_char skey[G_BDE_SKEYLEN];
	keyInstance ki;
	cipherInstance ci;
	

	AES_init(&ci);
	sc = wp->softc;
	o = 0;
	for (n = 0; o < wp->length; n++, o += sc->sectorsize) {
		d = (u_char *)wp->ksp->data + wp->ko + n * G_BDE_SKEYLEN;
		g_bde_kkey(sc, &ki, DIR_DECRYPT, wp->offset + o);
		AES_decrypt(&ci, &ki, d, skey, sizeof skey);
		d = (u_char *)wp->data + o;
		AES_makekey(&ki, DIR_DECRYPT, G_BDE_SKEYBITS, skey);
		AES_decrypt(&ci, &ki, d, d, sc->sectorsize);
	}
	bzero(skey, sizeof skey);
	bzero(&ci, sizeof ci);
	bzero(&ki, sizeof ki);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct g_bde_work {scalar_t__ length; int ko; scalar_t__ offset; TYPE_2__* ksp; TYPE_1__* sp; scalar_t__ data; struct g_bde_softc* softc; } ;
struct g_bde_softc {scalar_t__ sectorsize; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  keyInstance ;
typedef  int /*<<< orphan*/  cipherInstance ;
struct TYPE_4__ {scalar_t__ data; } ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_encrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  AES_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AES_makekey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DIR_ENCRYPT ; 
 int /*<<< orphan*/  G_BDE_SKEYBITS ; 
 int G_BDE_SKEYLEN ; 
 int /*<<< orphan*/  arc4rand (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  g_bde_kkey (struct g_bde_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

void
g_bde_crypt_write(struct g_bde_work *wp)
{
	u_char *s, *d;
	struct g_bde_softc *sc;
	u_int n;
	off_t o;
	u_char skey[G_BDE_SKEYLEN];
	keyInstance ki;
	cipherInstance ci;

	sc = wp->softc;
	AES_init(&ci);
	o = 0;
	for (n = 0; o < wp->length; n++, o += sc->sectorsize) {

		s = (u_char *)wp->data + o;
		d = (u_char *)wp->sp->data + o;
		arc4rand(skey, sizeof skey, 0);
		AES_makekey(&ki, DIR_ENCRYPT, G_BDE_SKEYBITS, skey);
		AES_encrypt(&ci, &ki, s, d, sc->sectorsize);

		d = (u_char *)wp->ksp->data + wp->ko + n * G_BDE_SKEYLEN;
		g_bde_kkey(sc, &ki, DIR_ENCRYPT, wp->offset + o);
		AES_encrypt(&ci, &ki, skey, d, sizeof skey);
		bzero(skey, sizeof skey);
	}
	bzero(skey, sizeof skey);
	bzero(&ci, sizeof ci);
	bzero(&ki, sizeof ki);
}
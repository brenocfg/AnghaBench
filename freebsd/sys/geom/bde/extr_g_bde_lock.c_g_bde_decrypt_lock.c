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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct g_bde_softc {int /*<<< orphan*/  consumer; int /*<<< orphan*/  sha2; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int G_BDE_MAXKEYS ; 
 int /*<<< orphan*/  SHA512_DIGEST_LENGTH ; 
 scalar_t__ bcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int g_bde_decrypt_lockx (struct g_bde_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_read_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int
g_bde_decrypt_lock(struct g_bde_softc *sc, u_char *keymat, u_char *meta, off_t mediasize, u_int sectorsize, u_int *nkey)
{
	u_char *buf, buf1[16];
	int error, e, i;

	/* set up the key-material */
	bcopy(keymat, sc->sha2, SHA512_DIGEST_LENGTH);

	/* If passed-in metadata is non-zero, use it */
	bzero(buf1, sizeof buf1);
	if (meta != NULL && bcmp(buf1, meta, sizeof buf1))
		return (g_bde_decrypt_lockx(sc, meta, mediasize,
		    sectorsize, nkey));

	/* Read sector zero */
	buf = g_read_data(sc->consumer, 0, sectorsize, &error);
	if (buf == NULL)
		return(error);

	/* Try each index in turn, save indicative errors for final result */
	error = EINVAL;
	for (i = 0; i < G_BDE_MAXKEYS; i++) {
		e = g_bde_decrypt_lockx(sc, buf + i * 16, mediasize,
		    sectorsize, nkey);
		/* Success or destroyed master key terminates */
		if (e == 0 || e == ENOENT) {
			error = e;
			break;
		}
		if (e != 0 && error == EINVAL)
			error = e;
	}
	g_free(buf);
	return (error);
}
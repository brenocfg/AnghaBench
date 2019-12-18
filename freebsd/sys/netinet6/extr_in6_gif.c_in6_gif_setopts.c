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
typedef  int u_int ;
struct gif_softc {scalar_t__ gif_family; int gif_options; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  CK_LIST_REMOVE (struct gif_softc*,int /*<<< orphan*/ ) ; 
 int GIF_IGNORE_SOURCE ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  chain ; 
 int /*<<< orphan*/  in6_gif_attach (struct gif_softc*) ; 
 int /*<<< orphan*/  srchash ; 

int
in6_gif_setopts(struct gif_softc *sc, u_int options)
{

	/* NOTE: we are protected with gif_ioctl_sx lock */
	MPASS(sc->gif_family == AF_INET6);
	MPASS(sc->gif_options != options);

	if ((options & GIF_IGNORE_SOURCE) !=
	    (sc->gif_options & GIF_IGNORE_SOURCE)) {
		CK_LIST_REMOVE(sc, srchash);
		CK_LIST_REMOVE(sc, chain);
		sc->gif_options = options;
		in6_gif_attach(sc);
	}
	return (0);
}
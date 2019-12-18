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
typedef  int /*<<< orphan*/  tbuf ;
struct tap_priv {int /*<<< orphan*/ * mevp; } ;
struct net_backend {int fd; scalar_t__ opaque; } ;
typedef  int /*<<< orphan*/ * net_be_rxeof_t ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_EVENT ; 
 int /*<<< orphan*/  CAP_READ ; 
 int /*<<< orphan*/  CAP_WRITE ; 
 int /*<<< orphan*/  EVF_READ ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  WPRINTF (char*) ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int caph_rights_limit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * mevent_add_disabled (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char const*,int) ; 
 int /*<<< orphan*/  tap_cleanup (struct net_backend*) ; 

__attribute__((used)) static int
tap_init(struct net_backend *be, const char *devname,
	 net_be_rxeof_t cb, void *param)
{
	struct tap_priv *priv = (struct tap_priv *)be->opaque;
	char tbuf[80];
	int opt = 1;
#ifndef WITHOUT_CAPSICUM
	cap_rights_t rights;
#endif

	if (cb == NULL) {
		WPRINTF(("TAP backend requires non-NULL callback\n"));
		return (-1);
	}

	strcpy(tbuf, "/dev/");
	strlcat(tbuf, devname, sizeof(tbuf));

	be->fd = open(tbuf, O_RDWR);
	if (be->fd == -1) {
		WPRINTF(("open of tap device %s failed\n", tbuf));
		goto error;
	}

	/*
	 * Set non-blocking and register for read
	 * notifications with the event loop
	 */
	if (ioctl(be->fd, FIONBIO, &opt) < 0) {
		WPRINTF(("tap device O_NONBLOCK failed\n"));
		goto error;
	}

#ifndef WITHOUT_CAPSICUM
	cap_rights_init(&rights, CAP_EVENT, CAP_READ, CAP_WRITE);
	if (caph_rights_limit(be->fd, &rights) == -1)
		errx(EX_OSERR, "Unable to apply rights for sandbox");
#endif

	priv->mevp = mevent_add_disabled(be->fd, EVF_READ, cb, param);
	if (priv->mevp == NULL) {
		WPRINTF(("Could not register event\n"));
		goto error;
	}

	return (0);

error:
	tap_cleanup(be);
	return (-1);
}
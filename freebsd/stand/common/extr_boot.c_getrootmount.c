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
typedef  int /*<<< orphan*/  lbuf ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ fgetstr (char*,int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 scalar_t__ isspace (char) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setenv (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 char* strdup (char const*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 

int
getrootmount(char *rootdev)
{
	char	lbuf[128], *cp, *ep, *dev, *fstyp, *options;
	int		fd, error;

	if (getenv("vfs.root.mountfrom") != NULL)
		return(0);

	error = 1;
	sprintf(lbuf, "%s/etc/fstab", rootdev);
	if ((fd = open(lbuf, O_RDONLY)) < 0)
		goto notfound;

	/* loop reading lines from /etc/fstab    What was that about sscanf again? */
	fstyp = NULL;
	dev = NULL;
	while (fgetstr(lbuf, sizeof(lbuf), fd) >= 0) {
		if ((lbuf[0] == 0) || (lbuf[0] == '#'))
			continue;

		/* skip device name */
		for (cp = lbuf; (*cp != 0) && !isspace(*cp); cp++)
			;
		if (*cp == 0)		/* misformatted */
			continue;
		/* delimit and save */
		*cp++ = 0;
		free(dev);
		dev = strdup(lbuf);

		/* skip whitespace up to mountpoint */
		while ((*cp != 0) && isspace(*cp))
			cp++;
		/* must have /<space> to be root */
		if ((*cp == 0) || (*cp != '/') || !isspace(*(cp + 1)))
			continue;
		/* skip whitespace up to fstype */
		cp += 2;
		while ((*cp != 0) && isspace(*cp))
			cp++;
		if (*cp == 0)		/* misformatted */
			continue;
		/* skip text to end of fstype and delimit */
		ep = cp;
		while ((*cp != 0) && !isspace(*cp))
			cp++;
		*cp = 0;
		free(fstyp);
		fstyp = strdup(ep);

		/* skip whitespace up to mount options */
		cp += 1;
		while ((*cp != 0) && isspace(*cp))
			cp++;
		if (*cp == 0)           /* misformatted */
			continue;
		/* skip text to end of mount options and delimit */
		ep = cp;
		while ((*cp != 0) && !isspace(*cp))
			cp++;
		*cp = 0;
		options = strdup(ep);
		/* Build the <fstype>:<device> and save it in vfs.root.mountfrom */
		sprintf(lbuf, "%s:%s", fstyp, dev);
		setenv("vfs.root.mountfrom", lbuf, 0);

		/* Don't override vfs.root.mountfrom.options if it is already set */
		if (getenv("vfs.root.mountfrom.options") == NULL) {
			/* save mount options */
			setenv("vfs.root.mountfrom.options", options, 0);
		}
		free(options);
		error = 0;
		break;
	}
	close(fd);
	free(dev);
	free(fstyp);

notfound:
	if (error) {
		const char *currdev;

		currdev = getenv("currdev");
		if (currdev != NULL && strncmp("zfs:", currdev, 4) == 0) {
			cp = strdup(currdev);
			cp[strlen(cp) - 1] = '\0';
			setenv("vfs.root.mountfrom", cp, 0);
			error = 0;
			free(cp);
		}
	}

	return(error);
}
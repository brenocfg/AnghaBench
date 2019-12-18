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

/* Variables and functions */
 int atoi (char*) ; 
 int read (int,char*,int) ; 
 int snprintf (char*,int,char*,int) ; 
 int sscanf (char*,char*,int*) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 char* strdup (char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnc (int /*<<< orphan*/ ,char*,...) ; 
 int write (int,char*,int) ; 

int
get_slot_info(int so, int slot, char **manuf, char **version, char
	      **device, int *state)
{
    int             rc = -1;
    int             rv;
    static char     buf[1024];
    int             slen;
    char           *s;
    char           *sl;

    char           *_manuf;
    char           *_version;
    char           *_device;

    if ((slen = snprintf(buf, sizeof buf, "N%d", slot)) < 0) {
	warnc(0, "write");
	goto err;
    }

    if ((rv = write(so, buf, slen)) < 0) {
	warn("write");
	goto err;
    } else if (rv != slen) {
	warnc(0, "write");
	goto err;
    }

    if ((rv = read(so, buf, sizeof buf)) < 0) {
	warn("read");
	goto err;
    }

    s = buf;
    if ((sl = strsep(&s, "~")) == NULL)
	goto parse_err;
    if (atoi(sl) != slot)
	goto parse_err;
    if ((_manuf = strsep(&s, "~")) == NULL)
	goto parse_err;
    if ((_version = strsep(&s, "~")) == NULL)
	goto parse_err;
    if ((_device = strsep(&s, "~")) == NULL)
	goto parse_err;
    if (sscanf(s, "%1d", state) != 1)
	goto parse_err;
    if (s != NULL && strchr(s, '~') != NULL)
	goto parse_err;

    if ((*manuf = strdup(_manuf)) == NULL) {
	warn("strdup");
	goto err;
    }
    if ((*version = strdup(_version)) == NULL) {
	warn("strdup");
	goto err;
    }
    if ((*device = strdup(_device)) == NULL) {
	warn("strdup");
	goto err;
    }
    if (*manuf == NULL || *version == NULL || *device == NULL) {
	warn("strdup");
	goto err;
    }

    rc = 0;
  err:
    return rc;
  parse_err:
    warnc(0, "Invalid response: %*s", rv, buf);
    return rc;
}
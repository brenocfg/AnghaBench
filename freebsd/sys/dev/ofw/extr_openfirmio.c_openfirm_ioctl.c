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
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct thread {int dummy; } ;
struct ofiocdesc {scalar_t__ of_nodeid; int of_buflen; int /*<<< orphan*/  of_name; int /*<<< orphan*/  of_namelen; int /*<<< orphan*/  of_buf; } ;
struct cdev {int dummy; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  newname ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int ENOENT ; 
 int ENOIOCTL ; 
 int ENOMEM ; 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
#define  OFIOCFINDDEVICE 135 
#define  OFIOCGET 134 
#define  OFIOCGETCHILD 133 
#define  OFIOCGETNEXT 132 
#define  OFIOCGETOPTNODE 131 
#define  OFIOCGETPROPLEN 130 
 int /*<<< orphan*/  OFIOCMAXVALUE ; 
#define  OFIOCNEXTPROP 129 
#define  OFIOCSET 128 
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_finddevice (char*) ; 
 int OF_getprop (scalar_t__,char*,void*,int) ; 
 int OF_getproplen (scalar_t__,char*) ; 
 int OF_nextprop (scalar_t__,char*,char*,int) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int OF_setprop (scalar_t__,char*,char*,int) ; 
 int copyin (int /*<<< orphan*/ ,char*,int) ; 
 int copyout (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ lastnode ; 
 char* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int openfirm_checkid (scalar_t__,scalar_t__) ; 
 int openfirm_getstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int
openfirm_ioctl(struct cdev *dev, u_long cmd, caddr_t data, int flags,
    struct thread *td)
{
	struct ofiocdesc *of;
	phandle_t node;
	int len, ok, error;
	char *name, *value;
	char newname[32];

	if ((flags & FREAD) == 0)
		return (EBADF);

	of = (struct ofiocdesc *)data;
	switch (cmd) {
	case OFIOCGETOPTNODE:
		*(phandle_t *) data = OF_finddevice("/options");
		return (0);
	case OFIOCGET:
	case OFIOCSET:
	case OFIOCNEXTPROP:
	case OFIOCFINDDEVICE:
	case OFIOCGETPROPLEN:
		node = of->of_nodeid;
		break;
	case OFIOCGETNEXT:
	case OFIOCGETCHILD:
		node = *(phandle_t *)data;
		break;
	default:
		return (ENOIOCTL);
	}

	if (node != 0 && node != lastnode) {
		/* Not an easy one, we must search for it. */
		ok = openfirm_checkid(OF_peer(0), node);
		if (!ok)
			return (EINVAL);
		lastnode = node;
	}

	name = value = NULL;
	error = 0;
	switch (cmd) {

	case OFIOCGET:
	case OFIOCGETPROPLEN:
		if (node == 0)
			return (EINVAL);
		error = openfirm_getstr(of->of_namelen, of->of_name, &name);
		if (error)
			break;
		len = OF_getproplen(node, name);
		if (cmd == OFIOCGETPROPLEN) {
			of->of_buflen = len;
			break;
		}
		if (len > of->of_buflen) {
			error = ENOMEM;
			break;
		}
		of->of_buflen = len;
		/* -1 means no entry; 0 means no value. */
		if (len <= 0)
			break;
		value = malloc(len, M_TEMP, M_WAITOK);
		len = OF_getprop(node, name, (void *)value, len);
		error = copyout(value, of->of_buf, len);
		break;

	case OFIOCSET:
		/*
		 * Note: Text string values for at least the /options node
		 * have to be null-terminated and the length parameter must
		 * include this terminating null.  However, like OF_getprop(),
		 * OF_setprop() will return the actual length of the text
		 * string, i.e. omitting the terminating null.
		 */
		if ((flags & FWRITE) == 0)
			return (EBADF);
		if (node == 0)
			return (EINVAL);
		if ((u_int)of->of_buflen > OFIOCMAXVALUE)
			return (ENAMETOOLONG);
		error = openfirm_getstr(of->of_namelen, of->of_name, &name);
		if (error)
			break;
		value = malloc(of->of_buflen, M_TEMP, M_WAITOK);
		error = copyin(of->of_buf, value, of->of_buflen);
		if (error)
			break;
		len = OF_setprop(node, name, value, of->of_buflen);
		if (len < 0)
			error = EINVAL;
		of->of_buflen = len;
		break;

	case OFIOCNEXTPROP:
		if (node == 0 || of->of_buflen < 0)
			return (EINVAL);
		if (of->of_namelen != 0) {
			error = openfirm_getstr(of->of_namelen, of->of_name,
			    &name);
			if (error)
				break;
		}
		ok = OF_nextprop(node, name, newname, sizeof(newname));
		if (ok == 0) {
			error = ENOENT;
			break;
		}
		if (ok == -1) {
			error = EINVAL;
			break;
		}
		len = strlen(newname) + 1;
		if (len > of->of_buflen)
			len = of->of_buflen;
		else
			of->of_buflen = len;
		error = copyout(newname, of->of_buf, len);
		break;

	case OFIOCGETNEXT:
		node = OF_peer(node);
		*(phandle_t *)data = lastnode = node;
		break;

	case OFIOCGETCHILD:
		if (node == 0)
			return (EINVAL);
		node = OF_child(node);
		*(phandle_t *)data = lastnode = node;
		break;

	case OFIOCFINDDEVICE:
		error = openfirm_getstr(of->of_namelen, of->of_name, &name);
		if (error)
			break;
		node = OF_finddevice(name);
		if (node == -1) {
			error = ENOENT;
			break;
		}
		of->of_nodeid = lastnode = node;
		break;
	}

	if (name != NULL)
		free(name, M_TEMP);
	if (value != NULL)
		free(value, M_TEMP);

	return (error);
}
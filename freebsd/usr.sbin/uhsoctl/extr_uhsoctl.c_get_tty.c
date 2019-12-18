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
struct ctx {char* ifnam; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 char* SYSCTL_LOCATION ; 
 char* SYSCTL_NAME_TTY ; 
 char* SYSCTL_NETIF ; 
 char* SYSCTL_TEST ; 
 char* TTY_NAME ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  memset (char**,int /*<<< orphan*/ ,int) ; 
 char** port_type_list ; 
 char** realloc (char**,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int sscanf (char const*,char*,int*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 char* strstr (char*,char*) ; 
 int sysctlbyname (char*,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char **
get_tty(struct ctx *ctx)
{
	char buf[64], data[128];
	int error, i, usbport, usbport0, list_size = 0;
	char **list = NULL;
	size_t len;
	const char **p, *q;
	
	/*
	 * Look for the network interface first
	 */
	for (i = 0; ; i++) {
		/* Check if we still have uhso nodes to check */
		snprintf(buf, 64, SYSCTL_TEST, i);
		len = 127;
		error = sysctlbyname(buf, data, &len, NULL, 0);
		data[len] = '\0';
#ifdef DEBUG
		fprintf(stderr, "sysctl %s returned(%d): %s\n",
		    buf, error, error == 0 ? data : "FAILED");
#endif
		if (error < 0 || strcasecmp(data, "uhso") != 0)
			return NULL;

		/* Check if this node contains the network interface we want */
		snprintf(buf, 64, SYSCTL_NETIF, i);
		len = 127;
		error = sysctlbyname(buf, data, &len, NULL, 0);
		data[len] = '\0';
#ifdef DEBUG
		fprintf(stderr, "sysctl %s returned(%d): %s\n",
		    buf, error, error == 0 ? data : "FAILED");
#endif
		if (error == 0 && strcasecmp(data, ctx->ifnam) == 0)
			break;
	}

	/* Figure out the USB port location */
	snprintf(buf, 64, SYSCTL_LOCATION, i);
	len = 127;
	error = sysctlbyname(buf, data, &len, NULL, 0);
	data[len] = '\0';
#ifdef DEBUG
	fprintf(stderr, "sysctl %s returned(%d): %s\n",
	    buf, error, error == 0 ? data : "FAILED");
#endif
	if (error != 0)
		return (NULL);

	q = strstr(data, "port=");
	if (q != NULL) {
		error = sscanf(q, " port=%d", &usbport);
		if (error != 1) {
#ifdef DEBUG
			fprintf(stderr, "failed to read usb port location from '%s'\n", data);
#endif
			return (NULL);
		}
	} else {
#ifdef DEBUG
			fprintf(stderr, "failed to parse location '%s'\n", data);
#endif
			return (NULL);
	}
#ifdef DEBUG
	fprintf(stderr, "USB port location=%d\n", usbport);
#endif

	/*
	 * Now go through it all again but only look at those matching the
	 * usb port location we found.
	 */
	for (i = 0; ; i++) {
		snprintf(buf, 64, SYSCTL_LOCATION, i);
		len = 127;
		memset(&data, 0, sizeof(data));
		error = sysctlbyname(buf, data, &len, NULL, 0);
		if (error != 0)
			break;
		data[len] = '\0';
		q = strstr(data, "port=");
		if (q == NULL)
			continue;
		sscanf(q, " port=%d", &usbport0);
		if (usbport != usbport0)
			continue;

		/* Try to add ports */	
		for (p = port_type_list; *p != NULL; p++) {
			snprintf(buf, 64, SYSCTL_NAME_TTY, i, *p);
			len = 127;
			memset(&data, 0, sizeof(data));
			error = sysctlbyname(buf, data, &len, NULL, 0);
			data[len] = '\0';
#ifdef DEBUG
			fprintf(stderr, "sysctl %s returned(%d): %s\n",
			    buf, error, error == 0 ? data : "FAILED");
#endif
			if (error == 0) {
				list = realloc(list, (list_size + 1) * sizeof(char *));
				list[list_size] = malloc(strlen(data) + strlen(TTY_NAME));
		    		sprintf(list[list_size], TTY_NAME, data);
		    		list_size++;
			}
		}
	}
	list = realloc(list, (list_size + 1) * sizeof(char *));
	list[list_size] = NULL;
	return (list);
}
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
 char* calloc (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 scalar_t__ read (int,char*,int) ; 
 int socket_connect (char*,char*) ; 
 scalar_t__ sprintf (char*,char*,...) ; 
 char* strdup (char const*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 char* strstr (char const*,char*) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (int,char*,int) ; 

__attribute__((used)) static int http_open(const char *fn)
{
	char *p, *proxy, *q, *http_host, *host, *port, *path, *buf;
	int fd, ret, l;

	/* parse URL; adapted from khttp_parse_url() in knetfile.c */
	if (strstr(fn, "http://") != fn) return 0;
	// set ->http_host
	for (p = (char*)fn + 7; *p && *p != '/'; ++p);
	l = p - fn - 7;
	http_host = calloc(l + 1, 1);
	strncpy(http_host, fn + 7, l);
	http_host[l] = 0;
	for (q = http_host; *q && *q != ':'; ++q);
	if (*q == ':') *q++ = 0;
	// get http_proxy
	proxy = getenv("http_proxy");
	// set host, port and path
	if (proxy == 0) {
		host = strdup(http_host); // when there is no proxy, server name is identical to http_host name.
		port = strdup(*q? q : "80");
		path = strdup(*p? p : "/");
	} else {
		host = (strstr(proxy, "http://") == proxy)? strdup(proxy + 7) : strdup(proxy);
		for (q = host; *q && *q != ':'; ++q);
		if (*q == ':') *q++ = 0; 
		port = strdup(*q? q : "80");
		path = strdup(fn);
	}

	/* connect; adapted from khttp_connect() in knetfile.c */
	l = 0;
	fd = socket_connect(host, port);
	buf = calloc(0x10000, 1); // FIXME: I am lazy... But in principle, 64KB should be large enough.
	l += sprintf(buf + l, "GET %s HTTP/1.0\r\nHost: %s\r\n", path, http_host);
	l += sprintf(buf + l, "\r\n");
	write(fd, buf, l);
	l = 0;
	while (read(fd, buf + l, 1)) { // read HTTP header; FIXME: bad efficiency
		if (buf[l] == '\n' && l >= 3)
			if (strncmp(buf + l - 3, "\r\n\r\n", 4) == 0) break;
		++l;
	}
	buf[l] = 0;
	if (l < 14) { // prematured header
		close(fd);
		fd = -1;
	}
	ret = strtol(buf + 8, &p, 0); // HTTP return code
	if (ret != 200) {
		close(fd);
		fd = -1;
	}
	free(buf); free(http_host); free(host); free(port); free(path);
	return fd;
}
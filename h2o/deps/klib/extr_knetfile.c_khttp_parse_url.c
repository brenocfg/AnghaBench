#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* http_host; char* host; int ctrl_fd; int fd; scalar_t__ seek_offset; int /*<<< orphan*/  type; void* path; void* port; } ;
typedef  TYPE_1__ knetFile ;

/* Variables and functions */
 int /*<<< orphan*/  KNF_TYPE_HTTP ; 
 scalar_t__ calloc (int,int) ; 
 char* getenv (char*) ; 
 void* strdup (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 char* strstr (char const*,char*) ; 

knetFile *khttp_parse_url(const char *fn, const char *mode)
{
	knetFile *fp;
	char *p, *proxy, *q;
	int l;
	if (strstr(fn, "http://") != fn) return 0;
	// set ->http_host
	for (p = (char*)fn + 7; *p && *p != '/'; ++p);
	l = p - fn - 7;
	fp = (knetFile*)calloc(1, sizeof(knetFile));
	fp->http_host = (char*)calloc(l + 1, 1);
	strncpy(fp->http_host, fn + 7, l);
	fp->http_host[l] = 0;
	for (q = fp->http_host; *q && *q != ':'; ++q);
	if (*q == ':') *q++ = 0;
	// get http_proxy
	proxy = getenv("http_proxy");
	// set ->host, ->port and ->path
	if (proxy == 0) {
		fp->host = strdup(fp->http_host); // when there is no proxy, server name is identical to http_host name.
		fp->port = strdup(*q? q : "80");
		fp->path = strdup(*p? p : "/");
	} else {
		fp->host = (strstr(proxy, "http://") == proxy)? strdup(proxy + 7) : strdup(proxy);
		for (q = fp->host; *q && *q != ':'; ++q);
		if (*q == ':') *q++ = 0; 
		fp->port = strdup(*q? q : "80");
		fp->path = strdup(fn);
	}
	fp->type = KNF_TYPE_HTTP;
	fp->ctrl_fd = fp->fd = -1;
	fp->seek_offset = 0;
	return fp;
}
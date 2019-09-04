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
typedef  int off_t ;
struct TYPE_3__ {int fd; char* path; char* http_host; scalar_t__ offset; int is_ready; int /*<<< orphan*/  port; int /*<<< orphan*/  host; } ;
typedef  TYPE_1__ knetFile ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ my_netread (int,char*,int) ; 
 int /*<<< orphan*/  netclose (int) ; 
 scalar_t__ netread (int,char*,int) ; 
 int /*<<< orphan*/  netwrite (int,char*,int) ; 
 int socket_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 

int khttp_connect_file(knetFile *fp)
{
	int ret, l = 0;
	char *buf, *p;
	if (fp->fd != -1) netclose(fp->fd);
	fp->fd = socket_connect(fp->host, fp->port);
	buf = (char*)calloc(0x10000, 1); // FIXME: I am lazy... But in principle, 64KB should be large enough.
	l += sprintf(buf + l, "GET %s HTTP/1.0\r\nHost: %s\r\n", fp->path, fp->http_host);
    l += sprintf(buf + l, "Range: bytes=%lld-\r\n", (long long)fp->offset);
	l += sprintf(buf + l, "\r\n");
	netwrite(fp->fd, buf, l);
	l = 0;
	while (netread(fp->fd, buf + l, 1)) { // read HTTP header; FIXME: bad efficiency
		if (buf[l] == '\n' && l >= 3)
			if (strncmp(buf + l - 3, "\r\n\r\n", 4) == 0) break;
		++l;
	}
	buf[l] = 0;
	if (l < 14) { // prematured header
		netclose(fp->fd);
		fp->fd = -1;
		return -1;
	}
	ret = strtol(buf + 8, &p, 0); // HTTP return code
	if (ret == 200 && fp->offset>0) { // 200 (complete result); then skip beginning of the file
		off_t rest = fp->offset;
		while (rest) {
			off_t l = rest < 0x10000? rest : 0x10000;
			rest -= my_netread(fp->fd, buf, l);
		}
	} else if (ret != 206 && ret != 200) {
		free(buf);
		fprintf(stderr, "[khttp_connect_file] fail to open file (HTTP code: %d).\n", ret);
		netclose(fp->fd);
		fp->fd = -1;
		return -1;
	}
	free(buf);
	fp->is_ready = 1;
	return 0;
}
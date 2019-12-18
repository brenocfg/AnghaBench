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
struct TYPE_3__ {int fd; char* host; int no_reconnect; char* retr; char* size_cmd; scalar_t__ seek_offset; int /*<<< orphan*/  port; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ knetFile ;

/* Variables and functions */
 int /*<<< orphan*/  KNF_TYPE_FTP ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 scalar_t__ strchr (char const*,char) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 char const* strstr (char const*,char*) ; 

knetFile *kftp_parse_url(const char *fn, const char *mode)
{
	knetFile *fp;
	char *p;
	int l;
	if (strstr(fn, "ftp://") != fn) return 0;
	for (p = (char*)fn + 6; *p && *p != '/'; ++p);
	if (*p != '/') return 0;
	l = p - fn - 6;
	fp = (knetFile*)calloc(1, sizeof(knetFile));
	fp->type = KNF_TYPE_FTP;
	fp->fd = -1;
	/* the Linux/Mac version of socket_connect() also recognizes a port
	 * like "ftp", but the Windows version does not. */
	fp->port = strdup("21");
	fp->host = (char*)calloc(l + 1, 1);
	if (strchr(mode, 'c')) fp->no_reconnect = 1;
	strncpy(fp->host, fn + 6, l);
	fp->retr = (char*)calloc(strlen(p) + 8, 1);
	sprintf(fp->retr, "RETR %s\r\n", p);
    fp->size_cmd = (char*)calloc(strlen(p) + 8, 1);
    sprintf(fp->size_cmd, "SIZE %s\r\n", p);
	fp->seek_offset = 0;
	return fp;
}
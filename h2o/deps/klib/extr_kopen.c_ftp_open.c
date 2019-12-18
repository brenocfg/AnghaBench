#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ctrl_fd; char* response; } ;
typedef  TYPE_1__ ftpaux_t ;

/* Variables and functions */
 char* calloc (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int kftp_get_response (TYPE_1__*) ; 
 int /*<<< orphan*/  kftp_send_cmd (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 void* socket_connect (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*,int*,int*,int*,int*,int*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 char const* strstr (char const*,char*) ; 

__attribute__((used)) static int ftp_open(const char *fn)
{
	char *p, *host = 0, *port = 0, *retr = 0;
	char host2[80], port2[10];
	int v[6], l, fd = -1, ret, pasv_port, pasv_ip[4];
	ftpaux_t aux;
	
	/* parse URL */
	if (strstr(fn, "ftp://") != fn) return 0;
	for (p = (char*)fn + 6; *p && *p != '/'; ++p);
	if (*p != '/') return 0;
	l = p - fn - 6;
	port = strdup("21");
	host = calloc(l + 1, 1);
	strncpy(host, fn + 6, l);
	retr = calloc(strlen(p) + 8, 1);
	sprintf(retr, "RETR %s\r\n", p);
	
	/* connect to ctrl */
	memset(&aux, 0, sizeof(ftpaux_t));
	aux.ctrl_fd = socket_connect(host, port);
	if (aux.ctrl_fd == -1) goto ftp_open_end; /* fail to connect ctrl */

	/* connect to the data stream */
	kftp_get_response(&aux);
	kftp_send_cmd(&aux, "USER anonymous\r\n", 1);
	kftp_send_cmd(&aux, "PASS kopen@\r\n", 1);
	kftp_send_cmd(&aux, "TYPE I\r\n", 1);
	kftp_send_cmd(&aux, "PASV\r\n", 1);
	for (p = aux.response; *p && *p != '('; ++p);
	if (*p != '(') goto ftp_open_end;
	++p;
	sscanf(p, "%d,%d,%d,%d,%d,%d", &v[0], &v[1], &v[2], &v[3], &v[4], &v[5]);
	memcpy(pasv_ip, v, 4 * sizeof(int));
	pasv_port = (v[4]<<8&0xff00) + v[5];
	kftp_send_cmd(&aux, retr, 0);
	sprintf(host2, "%d.%d.%d.%d", pasv_ip[0], pasv_ip[1], pasv_ip[2], pasv_ip[3]);
	sprintf(port2, "%d", pasv_port);
	fd = socket_connect(host2, port2);
	if (fd == -1) goto ftp_open_end;
	ret = kftp_get_response(&aux);
	if (ret != 150) {
		close(fd);
		fd = -1;
	}
	close(aux.ctrl_fd);

ftp_open_end:
	free(host); free(port); free(retr); free(aux.response);
	return fd;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int fd; char* size_cmd; char* response; long long file_size; scalar_t__ offset; char* retr; int is_ready; scalar_t__ no_reconnect; } ;
typedef  TYPE_1__ knetFile ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  int64tostr (char*,scalar_t__) ; 
 int kftp_get_response (TYPE_1__*) ; 
 int /*<<< orphan*/  kftp_pasv_connect (TYPE_1__*) ; 
 int /*<<< orphan*/  kftp_pasv_prep (TYPE_1__*) ; 
 int /*<<< orphan*/  kftp_send_cmd (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  netclose (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long long) ; 
 int sscanf (char*,char*,long long*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 long long strtoint64 (char const*) ; 

int kftp_connect_file(knetFile *fp)
{
	int ret;
	long long file_size;
	if (fp->fd != -1) {
		netclose(fp->fd);
		if (fp->no_reconnect) kftp_get_response(fp);
	}
	kftp_pasv_prep(fp);
    kftp_send_cmd(fp, fp->size_cmd, 1);
#ifndef _WIN32
    if ( sscanf(fp->response,"%*d %lld", &file_size) != 1 )
    {
        fprintf(stderr,"[kftp_connect_file] %s\n", fp->response);
        return -1;
    }
#else
	const char *p = fp->response;
	while (*p != ' ') ++p;
	while (*p < '0' || *p > '9') ++p;
	file_size = strtoint64(p);
#endif
	fp->file_size = file_size;
	if (fp->offset>=0) {
		char tmp[32];
#ifndef _WIN32
		sprintf(tmp, "REST %lld\r\n", (long long)fp->offset);
#else
		strcpy(tmp, "REST ");
		int64tostr(tmp + 5, fp->offset);
		strcat(tmp, "\r\n");
#endif
		kftp_send_cmd(fp, tmp, 1);
	}
	kftp_send_cmd(fp, fp->retr, 0);
	kftp_pasv_connect(fp);
	ret = kftp_get_response(fp);
	if (ret != 150) {
		fprintf(stderr, "[kftp_connect_file] %s\n", fp->response);
		netclose(fp->fd);
		fp->fd = -1;
		return -1;
	}
	fp->is_ready = 1;
	return 0;
}
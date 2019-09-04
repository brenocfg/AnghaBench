#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ctrl_fd; int fd; scalar_t__ type; struct TYPE_4__* http_host; struct TYPE_4__* path; struct TYPE_4__* retr; struct TYPE_4__* response; struct TYPE_4__* port; struct TYPE_4__* host; } ;
typedef  TYPE_1__ knetFile ;

/* Variables and functions */
 scalar_t__ KNF_TYPE_LOCAL ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  netclose (int) ; 

int knet_close(knetFile *fp)
{
	if (fp == 0) return 0;
	if (fp->ctrl_fd != -1) netclose(fp->ctrl_fd); // FTP specific
	if (fp->fd != -1) {
		/* On Linux/Mac, netclose() is an alias of close(), but on
		 * Windows, it is an alias of closesocket(). */
		if (fp->type == KNF_TYPE_LOCAL) close(fp->fd);
		else netclose(fp->fd);
	}
	free(fp->host); free(fp->port);
	free(fp->response); free(fp->retr); // FTP specific
	free(fp->path); free(fp->http_host); // HTTP specific
	free(fp);
	return 0;
}
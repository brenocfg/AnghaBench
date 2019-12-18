#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int fd; int ctrl_fd; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ knetFile ;

/* Variables and functions */
 int /*<<< orphan*/  KNF_TYPE_LOCAL ; 
 int O_BINARY ; 
 int O_RDONLY ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int kftp_connect (TYPE_1__*) ; 
 int /*<<< orphan*/  kftp_connect_file (TYPE_1__*) ; 
 TYPE_1__* kftp_parse_url (char const*,char const*) ; 
 int /*<<< orphan*/  khttp_connect_file (TYPE_1__*) ; 
 TYPE_1__* khttp_parse_url (char const*,char const*) ; 
 int /*<<< orphan*/  knet_close (TYPE_1__*) ; 
 int open (char const*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 
 char const* strstr (char const*,char*) ; 

knetFile *knet_open(const char *fn, const char *mode)
{
	knetFile *fp = 0;
	if (mode[0] != 'r') {
		fprintf(stderr, "[kftp_open] only mode \"r\" is supported.\n");
		return 0;
	}
	if (strstr(fn, "ftp://") == fn) {
		fp = kftp_parse_url(fn, mode);
		if (fp == 0) return 0;
		if (kftp_connect(fp) == -1) {
			knet_close(fp);
			return 0;
		}
		kftp_connect_file(fp);
	} else if (strstr(fn, "http://") == fn) {
		fp = khttp_parse_url(fn, mode);
		if (fp == 0) return 0;
		khttp_connect_file(fp);
	} else { // local file
#ifdef _WIN32
		/* In windows, O_BINARY is necessary. In Linux/Mac, O_BINARY may
		 * be undefined on some systems, although it is defined on my
		 * Mac and the Linux I have tested on. */
		int fd = open(fn, O_RDONLY | O_BINARY);
#else		
		int fd = open(fn, O_RDONLY);
#endif
		if (fd == -1) {
			perror("open");
			return 0;
		}
		fp = (knetFile*)calloc(1, sizeof(knetFile));
		fp->type = KNF_TYPE_LOCAL;
		fp->fd = fd;
		fp->ctrl_fd = -1;
	}
	if (fp && fp->fd == -1) {
		knet_close(fp);
		return 0;
	}
	return fp;
}
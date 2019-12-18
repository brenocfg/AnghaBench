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
struct TYPE_4__ {char* response; int pasv_port; int /*<<< orphan*/  pasv_ip; } ;
typedef  TYPE_1__ knetFile ;

/* Variables and functions */
 int /*<<< orphan*/  kftp_send_cmd (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*,int*,int*,int*,int*,int*) ; 

__attribute__((used)) static int kftp_pasv_prep(knetFile *ftp)
{
	char *p;
	int v[6];
	kftp_send_cmd(ftp, "PASV\r\n", 1);
	for (p = ftp->response; *p && *p != '('; ++p);
	if (*p != '(') return -1;
	++p;
	sscanf(p, "%d,%d,%d,%d,%d,%d", &v[0], &v[1], &v[2], &v[3], &v[4], &v[5]);
	memcpy(ftp->pasv_ip, v, 4 * sizeof(int));
	ftp->pasv_port = (v[4]<<8&0xff00) + v[5];
	return 0;
}
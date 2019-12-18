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
typedef  char u_char ;

/* Variables and functions */
 char FI ; 
 int IC735 ; 
 int /*<<< orphan*/  LOG_ERR ; 
 char PAD ; 
 char PR ; 
 char TX ; 
 char V_SFREQ ; 
 int /*<<< orphan*/  doublefreq (double,char*,int) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,...) ; 
 int write (int,char*,int) ; 

int
icom_freq(
	int fd,			/* file descriptor */
	int ident,		/* ICOM radio identifier */
	double freq		/* frequency (MHz) */
	)
{
	u_char cmd[] = {PAD, PR, PR, 0, TX, V_SFREQ, 0, 0, 0, 0, FI,
	    FI};
	int temp;
	int rc;

	cmd[3] = (char)ident;
	if (ident == IC735)
		temp = 4;
	else
		temp = 5;
	doublefreq(freq * 1e6, &cmd[6], temp);
	rc = write(fd, cmd, temp + 7);
	if (rc == -1) {
		msyslog(LOG_ERR, "icom_freq: write() failed: %m");
		return -1;
	} else if (rc != temp + 7) {
		msyslog(LOG_ERR, "icom_freq: only wrote %d of %d bytes.",
			rc, temp+7);
		return 1;
	}

	return 0;
}
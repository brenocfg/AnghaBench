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
typedef  int /*<<< orphan*/  conn_t ;

/* Variables and functions */
 int FTP_OK ; 
 int FTP_PROTOCOL_ERROR ; 
 int ftp_cmd (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int
ftp_mode_type(conn_t *conn, int mode, int type)
{
	int e;

	switch (mode) {
	case 0:
	case 's':
		mode = 'S';
	case 'S':
		break;
	default:
		return (FTP_PROTOCOL_ERROR);
	}
	if ((e = ftp_cmd(conn, "MODE %c", mode)) != FTP_OK) {
		if (mode == 'S') {
			/*
			 * Stream mode is supposed to be the default - so
			 * much so that some servers not only do not
			 * support any other mode, but do not support the
			 * MODE command at all.
			 *
			 * If "MODE S" fails, it is unlikely that we
			 * previously succeeded in setting a different
			 * mode.  Therefore, we simply hope that the
			 * server is already in the correct mode, and
			 * silently ignore the failure.
			 */
		} else {
			return (e);
		}
	}

	switch (type) {
	case 0:
	case 'i':
		type = 'I';
	case 'I':
		break;
	case 'a':
		type = 'A';
	case 'A':
		break;
	case 'd':
		type = 'D';
	case 'D':
		/* can't handle yet */
	default:
		return (FTP_PROTOCOL_ERROR);
	}
	if ((e = ftp_cmd(conn, "TYPE %c", type)) != FTP_OK)
		return (e);

	return (FTP_OK);
}
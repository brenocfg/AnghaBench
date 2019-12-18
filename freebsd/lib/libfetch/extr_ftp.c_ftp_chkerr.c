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
struct TYPE_4__ {char* buf; int buflen; int err; } ;
typedef  TYPE_1__ conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTP_PROTOCOL_ERROR ; 
 int fetch_getln (TYPE_1__*) ; 
 int /*<<< orphan*/  fetch_syserr () ; 
 int /*<<< orphan*/  ftp_seterr (int /*<<< orphan*/ ) ; 
 scalar_t__ isftpinfo (char*) ; 
 int /*<<< orphan*/  isftpreply (char*) ; 
 scalar_t__ isspace (unsigned char) ; 

__attribute__((used)) static int
ftp_chkerr(conn_t *conn)
{
	if (fetch_getln(conn) == -1) {
		fetch_syserr();
		return (-1);
	}
	if (isftpinfo(conn->buf)) {
		while (conn->buflen && !isftpreply(conn->buf)) {
			if (fetch_getln(conn) == -1) {
				fetch_syserr();
				return (-1);
			}
		}
	}

	while (conn->buflen &&
	    isspace((unsigned char)conn->buf[conn->buflen - 1]))
		conn->buflen--;
	conn->buf[conn->buflen] = '\0';

	if (!isftpreply(conn->buf)) {
		ftp_seterr(FTP_PROTOCOL_ERROR);
		return (-1);
	}

	conn->err = (conn->buf[0] - '0') * 100
	    + (conn->buf[1] - '0') * 10
	    + (conn->buf[2] - '0');

	return (conn->err);
}
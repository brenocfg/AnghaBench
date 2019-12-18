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
typedef  int ssize_t ;
struct TYPE_4__ {char* buf; size_t bufsize; size_t buflen; } ;
typedef  TYPE_1__ conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGF (char*,char*) ; 
 int /*<<< orphan*/  ENOMEM ; 
 size_t MIN_BUF_SIZE ; 
 int /*<<< orphan*/  errno ; 
 int fetch_read (TYPE_1__*,char*,int) ; 
 char* malloc (size_t) ; 
 char* realloc (char*,size_t) ; 

int
fetch_getln(conn_t *conn)
{
	char *tmp;
	size_t tmpsize;
	ssize_t len;
	char c;

	if (conn->buf == NULL) {
		if ((conn->buf = malloc(MIN_BUF_SIZE)) == NULL) {
			errno = ENOMEM;
			return (-1);
		}
		conn->bufsize = MIN_BUF_SIZE;
	}

	conn->buf[0] = '\0';
	conn->buflen = 0;

	do {
		len = fetch_read(conn, &c, 1);
		if (len == -1)
			return (-1);
		if (len == 0)
			break;
		conn->buf[conn->buflen++] = c;
		if (conn->buflen == conn->bufsize) {
			tmp = conn->buf;
			tmpsize = conn->bufsize * 2 + 1;
			if ((tmp = realloc(tmp, tmpsize)) == NULL) {
				errno = ENOMEM;
				return (-1);
			}
			conn->buf = tmp;
			conn->bufsize = tmpsize;
		}
	} while (c != '\n');

	conn->buf[conn->buflen] = '\0';
	DEBUGF("<<< %s", conn->buf);
	return (0);
}
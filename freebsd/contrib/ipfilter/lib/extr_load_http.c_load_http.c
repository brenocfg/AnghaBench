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
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_4__ {struct TYPE_4__* al_next; } ;
typedef  TYPE_1__ alist_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 scalar_t__ ISSPACE (char) ; 
 int LOAD_BUFSIZE ; 
 int MAX_URL_LEN ; 
 TYPE_1__* alist_new (int /*<<< orphan*/ ,char*) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int connecttcp (char*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int read (int,char*,int) ; 
 int snprintf (char*,size_t,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 
 int write (int,char*,int) ; 

alist_t *
load_http(char *url)
{
	int fd, len, left, port, endhdr, removed, linenum = 0;
	char *s, *t, *u, buffer[LOAD_BUFSIZE], *myurl;
	alist_t *a, *rtop, *rbot;
	size_t avail;
	int error;

	/*
	 * More than this would just be absurd.
	 */
	if (strlen(url) > MAX_URL_LEN) {
		fprintf(stderr, "load_http has a URL > %d bytes?!\n",
			MAX_URL_LEN);
		return NULL;
	}

	fd = -1;
	rtop = NULL;
	rbot = NULL;

	avail = sizeof(buffer);
	error = snprintf(buffer, avail, "GET %s HTTP/1.0\r\n", url);

	/*
	 * error is always less then avail due to the constraint on
	 * the url length above.
	 */
	avail -= error;

	myurl = strdup(url);
	if (myurl == NULL)
		goto done;

	s = myurl + 7;			/* http:// */
	t = strchr(s, '/');
	if (t == NULL) {
		fprintf(stderr, "load_http has a malformed URL '%s'\n", url);
		free(myurl);
		return NULL;
	}
	*t++ = '\0';

	/*
	 * 10 is the length of 'Host: \r\n\r\n' below.
	 */
	if (strlen(s) + strlen(buffer) + 10 > sizeof(buffer)) {
		fprintf(stderr, "load_http has a malformed URL '%s'\n", url);
		free(myurl);
		return NULL;
	}

	u = strchr(s, '@');
	if (u != NULL)
		s = u + 1;		/* AUTH */

	error = snprintf(buffer + strlen(buffer), avail, "Host: %s\r\n\r\n", s);
	if (error >= avail) {
		fprintf(stderr, "URL is too large: %s\n", url);
		goto done;
	}

	u = strchr(s, ':');
	if (u != NULL) {
		*u++ = '\0';
		port = atoi(u);
		if (port < 0 || port > 65535)
			goto done;
	} else {
		port = 80;
	}


	fd = connecttcp(s, port);
	if (fd == -1)
		goto done;


	len = strlen(buffer);
	if (write(fd, buffer, len) != len)
		goto done;

	s = buffer;
	endhdr = 0;
	left = sizeof(buffer) - 1;

	while ((len = read(fd, s, left)) > 0) {
		s[len] = '\0';
		left -= len;
		s += len;

		if (endhdr >= 0) {
			if (endhdr == 0) {
				t = strchr(buffer, ' ');
				if (t == NULL)
					continue;
				t++;
				if (*t != '2')
					break;
			}

			u = buffer;
			while ((t = strchr(u, '\r')) != NULL) {
				if (t == u) {
					if (*(t + 1) == '\n') {
						u = t + 2;
						endhdr = -1;
						break;
					} else
						t++;
				} else if (*(t + 1) == '\n') {
					endhdr++;
					u = t + 2;
				} else
					u = t + 1;
			}
			if (endhdr >= 0)
				continue;
			removed = (u - buffer) + 1;
			memmove(buffer, u, (sizeof(buffer) - left) - removed);
			s -= removed;
			left += removed;
		}

		do {
			t = strchr(buffer, '\n');
			if (t == NULL)
				break;

			linenum++;
			*t = '\0';

			/*
			 * Remove comment and continue to the next line if
			 * the comment is at the start of the line.
			 */
			u = strchr(buffer, '#');
			if (u != NULL) {
				*u = '\0';
				if (u == buffer)
					continue;
			}

			/*
			 * Trim off tailing white spaces, will include \r
			 */
			for (u = t - 1; (u >= buffer) && ISSPACE(*u); u--)
				*u = '\0';

			a = alist_new(AF_UNSPEC, buffer);
			if (a != NULL) {
				if (rbot != NULL)
					rbot->al_next = a;
				else
					rtop = a;
				rbot = a;
			} else {
				fprintf(stderr,
					"%s:%d unrecognised content:%s\n",
					url, linenum, buffer);
			}

			t++;
			removed = t - buffer;
			memmove(buffer, t, sizeof(buffer) - left - removed);
			s -= removed;
			left += removed;

		} while (1);
	}

done:
	if (myurl != NULL)
		free(myurl);
	if (fd != -1)
		close(fd);
	return rtop;
}
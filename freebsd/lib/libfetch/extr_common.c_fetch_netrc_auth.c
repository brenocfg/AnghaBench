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
struct url {int netrcfd; char const* host; char* user; char* pwd; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGF (char*,...) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  fetch_info (char*) ; 
 int fetch_netrc_open () ; 
 char* fetch_read_word (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int snprintf (char*,int,char*,char const*) ; 
 scalar_t__ strcasecmp (char const*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char const* strerror (int) ; 

int
fetch_netrc_auth(struct url *url)
{
	const char *word;
	int serrno;
	FILE *f;

	if (url->netrcfd < 0)
		url->netrcfd = fetch_netrc_open();
	if (url->netrcfd < 0)
		return (-1);
	if ((f = fdopen(url->netrcfd, "r")) == NULL) {
		serrno = errno;
		DEBUGF("fdopen(netrcfd): %s", strerror(errno));
		close(url->netrcfd);
		url->netrcfd = -1;
		errno = serrno;
		return (-1);
	}
	rewind(f);
	DEBUGF("searching netrc for %s\n", url->host);
	while ((word = fetch_read_word(f)) != NULL) {
		if (strcmp(word, "default") == 0) {
			DEBUGF("using default netrc settings\n");
			break;
		}
		if (strcmp(word, "machine") == 0 &&
		    (word = fetch_read_word(f)) != NULL &&
		    strcasecmp(word, url->host) == 0) {
			DEBUGF("using netrc settings for %s\n", word);
			break;
		}
	}
	if (word == NULL)
		goto ferr;
	while ((word = fetch_read_word(f)) != NULL) {
		if (strcmp(word, "login") == 0) {
			if ((word = fetch_read_word(f)) == NULL)
				goto ferr;
			if (snprintf(url->user, sizeof(url->user),
				"%s", word) > (int)sizeof(url->user)) {
				fetch_info("login name in .netrc is too long");
				url->user[0] = '\0';
			}
		} else if (strcmp(word, "password") == 0) {
			if ((word = fetch_read_word(f)) == NULL)
				goto ferr;
			if (snprintf(url->pwd, sizeof(url->pwd),
				"%s", word) > (int)sizeof(url->pwd)) {
				fetch_info("password in .netrc is too long");
				url->pwd[0] = '\0';
			}
		} else if (strcmp(word, "account") == 0) {
			if ((word = fetch_read_word(f)) == NULL)
				goto ferr;
			/* XXX not supported! */
		} else {
			break;
		}
	}
	fclose(f);
	url->netrcfd = -1;
	return (0);
ferr:
	serrno = errno;
	fclose(f);
	url->netrcfd = -1;
	errno = serrno;
	return (-1);
}
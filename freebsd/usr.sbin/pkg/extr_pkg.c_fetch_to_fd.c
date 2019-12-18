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
typedef  int /*<<< orphan*/  zone ;
struct url_stat {int dummy; } ;
struct url {char* scheme; char* host; int /*<<< orphan*/  port; } ;
struct dns_srvinfo {struct dns_srvinfo* next; int /*<<< orphan*/  port; int /*<<< orphan*/  host; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  MIRROR_TYPE ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ config_string (int /*<<< orphan*/ ,char const**) ; 
 struct dns_srvinfo* dns_getsrvinfo (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 struct url* fetchParseURL (char const*) ; 
 int /*<<< orphan*/ * fetchXGet (struct url*,struct url_stat*,char*) ; 
 scalar_t__ fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*) ; 
 scalar_t__ write (int,char*,scalar_t__) ; 

__attribute__((used)) static int
fetch_to_fd(const char *url, char *path)
{
	struct url *u;
	struct dns_srvinfo *mirrors, *current;
	struct url_stat st;
	FILE *remote;
	/* To store _https._tcp. + hostname + \0 */
	int fd;
	int retry, max_retry;
	ssize_t r;
	char buf[10240];
	char zone[MAXHOSTNAMELEN + 13];
	static const char *mirror_type = NULL;

	max_retry = 3;
	current = mirrors = NULL;
	remote = NULL;

	if (mirror_type == NULL && config_string(MIRROR_TYPE, &mirror_type)
	    != 0) {
		warnx("No MIRROR_TYPE defined");
		return (-1);
	}

	if ((fd = mkstemp(path)) == -1) {
		warn("mkstemp()");
		return (-1);
	}

	retry = max_retry;

	if ((u = fetchParseURL(url)) == NULL) {
		warn("fetchParseURL('%s')", url);
		return (-1);
	}

	while (remote == NULL) {
		if (retry == max_retry) {
			if (strcmp(u->scheme, "file") != 0 &&
			    strcasecmp(mirror_type, "srv") == 0) {
				snprintf(zone, sizeof(zone),
				    "_%s._tcp.%s", u->scheme, u->host);
				mirrors = dns_getsrvinfo(zone);
				current = mirrors;
			}
		}

		if (mirrors != NULL) {
			strlcpy(u->host, current->host, sizeof(u->host));
			u->port = current->port;
		}

		remote = fetchXGet(u, &st, "");
		if (remote == NULL) {
			--retry;
			if (retry <= 0)
				goto fetchfail;
			if (mirrors == NULL) {
				sleep(1);
			} else {
				current = current->next;
				if (current == NULL)
					current = mirrors;
			}
		}
	}

	while ((r = fread(buf, 1, sizeof(buf), remote)) > 0) {
		if (write(fd, buf, r) != r) {
			warn("write()");
			goto fetchfail;
		}
	}

	if (r != 0) {
		warn("An error occurred while fetching pkg(8)");
		goto fetchfail;
	}

	if (ferror(remote))
		goto fetchfail;

	goto cleanup;

fetchfail:
	if (fd != -1) {
		close(fd);
		fd = -1;
		unlink(path);
	}

cleanup:
	if (remote != NULL)
		fclose(remote);

	return fd;
}
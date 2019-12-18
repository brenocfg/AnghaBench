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
struct oidname {int dummy; } ;
struct oid {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SHUT_WR ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 scalar_t__ buf_gzip (char*,size_t,char*,size_t*) ; 
 int /*<<< orphan*/  dprintf (int /*<<< orphan*/ ,char*,char const*,size_t) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt (int,char**,char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  oid_get_by_name (struct oid*,char*) ; 
 scalar_t__ oid_get_next (struct oid*,struct oid*) ; 
 int /*<<< orphan*/  oid_get_root (struct oid*) ; 
 scalar_t__ oid_is_beneath (struct oid*,struct oid*) ; 
 int /*<<< orphan*/  oid_print (struct oid*,struct oidname*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidname_init (struct oidname*) ; 
 int /*<<< orphan*/ * open_memstream (char**,size_t*) ; 
 scalar_t__ optind ; 
 scalar_t__ read (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,size_t) ; 

int
main(int argc, char *argv[])
{
	struct oidname on;
	char *http_buf;
	FILE *fp;
	size_t http_buflen;
	int ch;
	bool gzip_mode, http_mode, print_descriptions;

	/* Parse command line flags. */
	gzip_mode = http_mode = print_descriptions = false;
	while ((ch = getopt(argc, argv, "dgh")) != -1) {
		switch (ch) {
		case 'd':
			print_descriptions = true;
			break;
		case 'g':
			gzip_mode = true;
			break;
		case 'h':
			http_mode = true;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	/* HTTP output: cache metrics in buffer. */
	if (http_mode) {
		fp = open_memstream(&http_buf, &http_buflen);
		if (fp == NULL)
			err(1, "open_memstream");
	} else {
		fp = stdout;
	}

	oidname_init(&on);
	if (argc == 0) {
		struct oid o;

		/* Print all OIDs. */
		oid_get_root(&o);
		do {
			oid_print(&o, &on, print_descriptions, fp);
		} while (oid_get_next(&o, &o));
	} else {
		int i;

		/* Print only trees provided as arguments. */
		for (i = 0; i < argc; ++i) {
			struct oid o, root;

			oid_get_by_name(&root, argv[i]);
			o = root;
			do {
				oid_print(&o, &on, print_descriptions, fp);
			} while (oid_get_next(&o, &o) &&
			    oid_is_beneath(&o, &root));
		}
	}

	if (http_mode) {
		const char *content_encoding = "";

		if (ferror(fp) || fclose(fp) != 0)
			err(1, "Cannot generate output");

		/* Gzip compress the output. */
		if (gzip_mode) {
			char *buf;
			size_t buflen;

			buflen = http_buflen;
			buf = malloc(buflen);
			if (buf == NULL)
				err(1, "Cannot allocate compression buffer");
			if (buf_gzip(http_buf, http_buflen, buf, &buflen)) {
				content_encoding = "Content-Encoding: gzip\r\n";
				free(http_buf);
				http_buf = buf;
				http_buflen = buflen;
			} else {
				free(buf);
			}
		}

		/* Print HTTP header and metrics. */
		dprintf(STDOUT_FILENO,
		    "HTTP/1.1 200 OK\r\n"
		    "Connection: close\r\n"
		    "%s"
		    "Content-Length: %zu\r\n"
		    "Content-Type: text/plain; version=0.0.4\r\n"
		    "\r\n",
		    content_encoding, http_buflen);
		write(STDOUT_FILENO, http_buf, http_buflen);
		free(http_buf);

		/* Drain output. */
		if (shutdown(STDIN_FILENO, SHUT_WR) == 0) {
			char buf[1024];

			while (read(STDIN_FILENO, buf, sizeof(buf)) > 0) {
			}
		}
	}
	return (0);
}
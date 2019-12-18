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
struct sig_cert {int siglen; int /*<<< orphan*/  cert; void* certlen; void* sig; } ;
struct sbuf {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 void* calloc (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int dup (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sbuf_bcat (struct sbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 void* sbuf_len (struct sbuf*) ; 
 struct sbuf* sbuf_new_auto () ; 
 int /*<<< orphan*/  sbuf_setpos (struct sbuf*,void*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static struct sig_cert *
parse_cert(int fd) {
	int my_fd;
	struct sig_cert *sc;
	FILE *fp;
	struct sbuf *buf, *sig, *cert;
	char *line;
	size_t linecap;
	ssize_t linelen;

	buf = NULL;
	my_fd = -1;
	sc = NULL;
	line = NULL;
	linecap = 0;

	if (lseek(fd, 0, 0) == -1) {
		warn("lseek");
		return (NULL);
	}

	/* Duplicate the fd so that fclose(3) does not close it. */
	if ((my_fd = dup(fd)) == -1) {
		warnx("dup");
		return (NULL);
	}

	if ((fp = fdopen(my_fd, "rb")) == NULL) {
		warn("fdopen");
		close(my_fd);
		return (NULL);
	}

	sig = sbuf_new_auto();
	cert = sbuf_new_auto();

	while ((linelen = getline(&line, &linecap, fp)) > 0) {
		if (strcmp(line, "SIGNATURE\n") == 0) {
			buf = sig;
			continue;
		} else if (strcmp(line, "CERT\n") == 0) {
			buf = cert;
			continue;
		} else if (strcmp(line, "END\n") == 0) {
			break;
		}
		if (buf != NULL)
			sbuf_bcat(buf, line, linelen);
	}

	fclose(fp);

	/* Trim out unrelated trailing newline */
	sbuf_setpos(sig, sbuf_len(sig) - 1);

	sbuf_finish(sig);
	sbuf_finish(cert);

	sc = calloc(1, sizeof(struct sig_cert));
	sc->siglen = sbuf_len(sig);
	sc->sig = calloc(1, sc->siglen);
	memcpy(sc->sig, sbuf_data(sig), sc->siglen);

	sc->certlen = sbuf_len(cert);
	sc->cert = strdup(sbuf_data(cert));

	sbuf_delete(sig);
	sbuf_delete(cert);

	return (sc);
}
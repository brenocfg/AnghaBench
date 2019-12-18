#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int s_addr; } ;
struct sockaddr_in {int ai_addrlen; int /*<<< orphan*/  cont; int /*<<< orphan*/  sin_port; TYPE_2__ sin_addr; int /*<<< orphan*/  sin_family; struct sockaddr* ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; struct sockaddr_in* ai_next; } ;
struct sockaddr {int dummy; } ;
struct imap_store {char* name; char* prefix; struct imap* imap; } ;
struct imap_server_conf {char* host; char* auth_method; char* user; int /*<<< orphan*/  pass; int /*<<< orphan*/  ssl_verify; scalar_t__ use_ssl; int /*<<< orphan*/  port; scalar_t__ tunnel; } ;
struct imap_cmd_cb {int ai_addrlen; int /*<<< orphan*/  cont; int /*<<< orphan*/  sin_port; TYPE_2__ sin_addr; int /*<<< orphan*/  sin_family; struct sockaddr* ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; struct imap_cmd_cb* ai_next; } ;
struct TYPE_4__ {int* fd; int /*<<< orphan*/  ssl; } ;
struct TYPE_6__ {TYPE_1__ sock; } ;
struct imap {TYPE_3__ buf; int /*<<< orphan*/  caps; int /*<<< orphan*/  in_progress; int /*<<< orphan*/ * in_progress_append; } ;
struct hostent {scalar_t__* h_addr_list; } ;
struct credential {scalar_t__ username; } ;
struct child_process {int use_shell; int in; int out; int /*<<< orphan*/  args; } ;
struct addrinfo {int ai_addrlen; int /*<<< orphan*/  cont; int /*<<< orphan*/  sin_port; TYPE_2__ sin_addr; int /*<<< orphan*/  sin_family; struct sockaddr* ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; struct addrinfo* ai_next; } ;
typedef  int /*<<< orphan*/  portstr ;
typedef  int /*<<< orphan*/  hints ;
typedef  int /*<<< orphan*/  cb ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AUTH_CRAM_MD5 ; 
 scalar_t__ CAP (int /*<<< orphan*/ ) ; 
 struct child_process CHILD_PROCESS_INIT ; 
 struct credential CREDENTIAL_INIT ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int NI_MAXHOST ; 
 int /*<<< orphan*/  NI_NUMERICHOST ; 
 int /*<<< orphan*/  NOLOGIN ; 
 int /*<<< orphan*/  PF_INET ; 
#define  RESP_BAD 130 
#define  RESP_NO 129 
#define  RESP_OK 128 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  STARTTLS ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  auth_cram_md5 ; 
 scalar_t__ buffer_gets (TYPE_3__*,char**) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  credential_approve (struct credential*) ; 
 int /*<<< orphan*/  credential_clear (struct credential*) ; 
 int /*<<< orphan*/  credential_reject (struct credential*) ; 
 int /*<<< orphan*/  die (char*,scalar_t__) ; 
 int dup (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeaddrinfo (struct sockaddr_in*) ; 
 char* gai_strerror (int) ; 
 int getaddrinfo (char*,char*,struct sockaddr_in*,struct sockaddr_in**) ; 
 struct hostent* gethostbyname (char*) ; 
 int /*<<< orphan*/  getnameinfo (struct sockaddr*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imap_close_store (struct imap_store*) ; 
 scalar_t__ const imap_exec (struct imap_store*,struct sockaddr_in*,char*,...) ; 
 int /*<<< orphan*/  imap_info (char*,...) ; 
 int /*<<< orphan*/  imap_warn (char*) ; 
 int /*<<< orphan*/  inet_ntoa (TYPE_2__) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 char* next_arg (char**) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_response_code (struct imap_store*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  server_fill_credential (struct imap_server_conf*,struct credential*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ssl_socket_connect (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ start_command (struct child_process*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 void* xcalloc (int,int) ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct imap_store *imap_open_store(struct imap_server_conf *srvc, char *folder)
{
	struct credential cred = CREDENTIAL_INIT;
	struct imap_store *ctx;
	struct imap *imap;
	char *arg, *rsp;
	int s = -1, preauth;

	ctx = xcalloc(1, sizeof(*ctx));

	ctx->imap = imap = xcalloc(1, sizeof(*imap));
	imap->buf.sock.fd[0] = imap->buf.sock.fd[1] = -1;
	imap->in_progress_append = &imap->in_progress;

	/* open connection to IMAP server */

	if (srvc->tunnel) {
		struct child_process tunnel = CHILD_PROCESS_INIT;

		imap_info("Starting tunnel '%s'... ", srvc->tunnel);

		argv_array_push(&tunnel.args, srvc->tunnel);
		tunnel.use_shell = 1;
		tunnel.in = -1;
		tunnel.out = -1;
		if (start_command(&tunnel))
			die("cannot start proxy %s", srvc->tunnel);

		imap->buf.sock.fd[0] = tunnel.out;
		imap->buf.sock.fd[1] = tunnel.in;

		imap_info("ok\n");
	} else {
#ifndef NO_IPV6
		struct addrinfo hints, *ai0, *ai;
		int gai;
		char portstr[6];

		xsnprintf(portstr, sizeof(portstr), "%d", srvc->port);

		memset(&hints, 0, sizeof(hints));
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		imap_info("Resolving %s... ", srvc->host);
		gai = getaddrinfo(srvc->host, portstr, &hints, &ai);
		if (gai) {
			fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(gai));
			goto bail;
		}
		imap_info("ok\n");

		for (ai0 = ai; ai; ai = ai->ai_next) {
			char addr[NI_MAXHOST];

			s = socket(ai->ai_family, ai->ai_socktype,
				   ai->ai_protocol);
			if (s < 0)
				continue;

			getnameinfo(ai->ai_addr, ai->ai_addrlen, addr,
				    sizeof(addr), NULL, 0, NI_NUMERICHOST);
			imap_info("Connecting to [%s]:%s... ", addr, portstr);

			if (connect(s, ai->ai_addr, ai->ai_addrlen) < 0) {
				close(s);
				s = -1;
				perror("connect");
				continue;
			}

			break;
		}
		freeaddrinfo(ai0);
#else /* NO_IPV6 */
		struct hostent *he;
		struct sockaddr_in addr;

		memset(&addr, 0, sizeof(addr));
		addr.sin_port = htons(srvc->port);
		addr.sin_family = AF_INET;

		imap_info("Resolving %s... ", srvc->host);
		he = gethostbyname(srvc->host);
		if (!he) {
			perror("gethostbyname");
			goto bail;
		}
		imap_info("ok\n");

		addr.sin_addr.s_addr = *((int *) he->h_addr_list[0]);

		s = socket(PF_INET, SOCK_STREAM, 0);

		imap_info("Connecting to %s:%hu... ", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
		if (connect(s, (struct sockaddr *)&addr, sizeof(addr))) {
			close(s);
			s = -1;
			perror("connect");
		}
#endif
		if (s < 0) {
			fputs("Error: unable to connect to server.\n", stderr);
			goto bail;
		}

		imap->buf.sock.fd[0] = s;
		imap->buf.sock.fd[1] = dup(s);

		if (srvc->use_ssl &&
		    ssl_socket_connect(&imap->buf.sock, 0, srvc->ssl_verify)) {
			close(s);
			goto bail;
		}
		imap_info("ok\n");
	}

	/* read the greeting string */
	if (buffer_gets(&imap->buf, &rsp)) {
		fprintf(stderr, "IMAP error: no greeting response\n");
		goto bail;
	}
	arg = next_arg(&rsp);
	if (!arg || *arg != '*' || (arg = next_arg(&rsp)) == NULL) {
		fprintf(stderr, "IMAP error: invalid greeting response\n");
		goto bail;
	}
	preauth = 0;
	if (!strcmp("PREAUTH", arg))
		preauth = 1;
	else if (strcmp("OK", arg) != 0) {
		fprintf(stderr, "IMAP error: unknown greeting response\n");
		goto bail;
	}
	parse_response_code(ctx, NULL, rsp);
	if (!imap->caps && imap_exec(ctx, NULL, "CAPABILITY") != RESP_OK)
		goto bail;

	if (!preauth) {
#ifndef NO_OPENSSL
		if (!srvc->use_ssl && CAP(STARTTLS)) {
			if (imap_exec(ctx, NULL, "STARTTLS") != RESP_OK)
				goto bail;
			if (ssl_socket_connect(&imap->buf.sock, 1,
					       srvc->ssl_verify))
				goto bail;
			/* capabilities may have changed, so get the new capabilities */
			if (imap_exec(ctx, NULL, "CAPABILITY") != RESP_OK)
				goto bail;
		}
#endif
		imap_info("Logging in...\n");
		server_fill_credential(srvc, &cred);

		if (srvc->auth_method) {
			struct imap_cmd_cb cb;

			if (!strcmp(srvc->auth_method, "CRAM-MD5")) {
				if (!CAP(AUTH_CRAM_MD5)) {
					fprintf(stderr, "You specified "
						"CRAM-MD5 as authentication method, "
						"but %s doesn't support it.\n", srvc->host);
					goto bail;
				}
				/* CRAM-MD5 */

				memset(&cb, 0, sizeof(cb));
				cb.cont = auth_cram_md5;
				if (imap_exec(ctx, &cb, "AUTHENTICATE CRAM-MD5") != RESP_OK) {
					fprintf(stderr, "IMAP error: AUTHENTICATE CRAM-MD5 failed\n");
					goto bail;
				}
			} else {
				fprintf(stderr, "Unknown authentication method:%s\n", srvc->host);
				goto bail;
			}
		} else {
			if (CAP(NOLOGIN)) {
				fprintf(stderr, "Skipping account %s@%s, server forbids LOGIN\n",
					srvc->user, srvc->host);
				goto bail;
			}
			if (!imap->buf.sock.ssl)
				imap_warn("*** IMAP Warning *** Password is being "
					  "sent in the clear\n");
			if (imap_exec(ctx, NULL, "LOGIN \"%s\" \"%s\"", srvc->user, srvc->pass) != RESP_OK) {
				fprintf(stderr, "IMAP error: LOGIN failed\n");
				goto bail;
			}
		}
	} /* !preauth */

	if (cred.username)
		credential_approve(&cred);
	credential_clear(&cred);

	/* check the target mailbox exists */
	ctx->name = folder;
	switch (imap_exec(ctx, NULL, "EXAMINE \"%s\"", ctx->name)) {
	case RESP_OK:
		/* ok */
		break;
	case RESP_BAD:
		fprintf(stderr, "IMAP error: could not check mailbox\n");
		goto out;
	case RESP_NO:
		if (imap_exec(ctx, NULL, "CREATE \"%s\"", ctx->name) == RESP_OK) {
			imap_info("Created missing mailbox\n");
		} else {
			fprintf(stderr, "IMAP error: could not create missing mailbox\n");
			goto out;
		}
		break;
	}

	ctx->prefix = "";
	return ctx;

bail:
	if (cred.username)
		credential_reject(&cred);
	credential_clear(&cred);

 out:
	imap_close_store(ctx);
	return NULL;
}
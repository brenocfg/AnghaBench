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
struct client {char* name; int salen; int capabilities; char* moniker; int child; int /*<<< orphan*/  thr; int /*<<< orphan*/ * logsock; int /*<<< orphan*/  target_name; int /*<<< orphan*/ * sock; void* sa; } ;
struct addrinfo {int ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; struct addrinfo* ai_next; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 int HAS_MONIKER ; 
 int ISSERVER ; 
 int /*<<< orphan*/  PF_UNSPEC ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 struct client** clients ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,int /*<<< orphan*/ ,int) ; 
 void* ecalloc (int,int) ; 
 struct client** erealloc (struct client**,int) ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 void* estrdup (char const*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int fork () ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  get_moniker (struct client*,char**) ; 
 int /*<<< orphan*/  get_targetname (struct client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_version_capa (struct client*,int /*<<< orphan*/ *,int*,char**) ; 
 int getaddrinfo (char*,char*,struct addrinfo*,struct addrinfo**) ; 
 void* krb5_storage_from_fd (int) ; 
 int /*<<< orphan*/  log_function (struct client*) ; 
 scalar_t__ logfile ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int num_clients ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (struct client*),struct client*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int wait_log (struct client*) ; 

__attribute__((used)) static void
connect_client(const char *slave)
{
    char *name, *port;
    struct client *c = ecalloc(1, sizeof(*c));
    struct addrinfo hints, *res0, *res;
    int ret, fd;

    name = estrdup(slave);
    port = strchr(name, ':');
    if (port == NULL)
	errx(1, "port missing from %s", name);
    *port++ = 0;

    c->name = estrdup(slave);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    ret = getaddrinfo(name, port, &hints, &res0);
    if (ret)
	errx(1, "error resolving %s", name);

    for (res = res0, fd = -1; res; res = res->ai_next) {
	fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (fd < 0)
	    continue;
	if (connect(fd, res->ai_addr, res->ai_addrlen) < 0) {
	    close(fd);
	    fd = -1;
	    continue;
	}
	c->sa = ecalloc(1, res->ai_addrlen);
	memcpy(c->sa, res->ai_addr, res->ai_addrlen);
	c->salen = res->ai_addrlen;
	break;  /* okay we got one */
    }
    if (fd < 0)
	err(1, "connect to host: %s", name);
    freeaddrinfo(res);

    c->sock = krb5_storage_from_fd(fd);
    close(fd);
    if (c->sock == NULL)
	errx(1, "krb5_storage_from_fd");

    {
	int32_t version;
	char *str = NULL;
	get_version_capa(c, &version, &c->capabilities, &str);
	if (str) {
	    free(str);
	}
	if (c->capabilities & HAS_MONIKER)
	    get_moniker(c, &c->moniker);
	else
	    c->moniker = c->name;
	if (c->capabilities & ISSERVER)
	    get_targetname(c, &c->target_name);
    }

    if (logfile) {
	int fd;

	printf("starting log socket to client %s\n", c->moniker);

	fd = wait_log(c);

	c->logsock = krb5_storage_from_fd(fd);
	close(fd);
	if (c->logsock == NULL)
	    errx(1, "failed to create log krb5_storage");
#ifdef ENABLE_PTHREAD_SUPPORT
	pthread_create(&c->thr, NULL, log_function, c);
#else
	c->child = fork();
	if (c->child == -1)
	    errx(1, "failed to fork");
	else if (c->child == 0) {
	    log_function(c);
	    fclose(logfile);
	    exit(0);
	}
#endif
   }


    clients = erealloc(clients, (num_clients + 1) * sizeof(*clients));

    clients[num_clients] = c;
    num_clients++;

    free(name);
}
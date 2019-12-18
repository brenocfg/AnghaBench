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
typedef  scalar_t__ uid_t ;
struct listen_port {int fd; struct listen_port* next; } ;
struct config_file {int /*<<< orphan*/  use_systemd; int /*<<< orphan*/  ip_freebind; int /*<<< orphan*/  ip_transparent; scalar_t__* username; } ;
struct addrinfo {int ai_flags; int /*<<< orphan*/  ai_socktype; } ;
typedef  int /*<<< orphan*/  port ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 int AI_NUMERICHOST ; 
 int AI_PASSIVE ; 
 int EAI_NONAME ; 
 int EAI_SYSTEM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int S_IRGRP ; 
 int S_IRUSR ; 
 int S_IWGRP ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 scalar_t__ calloc (int,int) ; 
 scalar_t__ cfg_gid ; 
 scalar_t__ cfg_uid ; 
 int /*<<< orphan*/  chmod (char const*,int /*<<< orphan*/ ) ; 
 int chown (char const*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 int create_local_accept_sock (char const*,int*,int /*<<< orphan*/ ) ; 
 int create_tcp_accept_sock (struct addrinfo*,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char const*,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  log_assert (char const*) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,char const*,scalar_t__) ; 

__attribute__((used)) static int
add_open(const char* ip, int nr, struct listen_port** list, int noproto_is_err,
	struct config_file* cfg)
{
	struct addrinfo hints;
	struct addrinfo* res;
	struct listen_port* n;
	int noproto = 0;
	int fd, r;
	char port[15];
	snprintf(port, sizeof(port), "%d", nr);
	port[sizeof(port)-1]=0;
	memset(&hints, 0, sizeof(hints));
	log_assert(ip);

	if(ip[0] == '/') {
		/* This looks like a local socket */
		fd = create_local_accept_sock(ip, &noproto, cfg->use_systemd);
		/*
		 * Change socket ownership and permissions so users other
		 * than root can access it provided they are in the same
		 * group as the user we run as.
		 */
		if(fd != -1) {
#ifdef HAVE_CHOWN
			if (cfg->username && cfg->username[0] &&
				cfg_uid != (uid_t)-1) {
				if(chown(ip, cfg_uid, cfg_gid) == -1)
					verbose(VERB_QUERY, "cannot chown %u.%u %s: %s",
					  (unsigned)cfg_uid, (unsigned)cfg_gid,
					  ip, strerror(errno));
			}
			chmod(ip, (mode_t)(S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP));
#else
			(void)cfg;
#endif
		}
	} else {
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_flags = AI_PASSIVE | AI_NUMERICHOST;
		if((r = getaddrinfo(ip, port, &hints, &res)) != 0 || !res) {
#ifdef USE_WINSOCK
			if(!noproto_is_err && r == EAI_NONAME) {
				/* tried to lookup the address as name */
				return 1; /* return success, but do nothing */
			}
#endif /* USE_WINSOCK */
			log_err("control interface %s:%s getaddrinfo: %s %s",
				ip?ip:"default", port, gai_strerror(r),
#ifdef EAI_SYSTEM
				r==EAI_SYSTEM?(char*)strerror(errno):""
#else
				""
#endif
			);
			return 0;
		}

		/* open fd */
		fd = create_tcp_accept_sock(res, 1, &noproto, 0,
			cfg->ip_transparent, 0, cfg->ip_freebind, cfg->use_systemd);
		freeaddrinfo(res);
	}

	if(fd == -1 && noproto) {
		if(!noproto_is_err)
			return 1; /* return success, but do nothing */
		log_err("cannot open control interface %s %d : "
			"protocol not supported", ip, nr);
		return 0;
	}
	if(fd == -1) {
		log_err("cannot open control interface %s %d", ip, nr);
		return 0;
	}

	/* alloc */
	n = (struct listen_port*)calloc(1, sizeof(*n));
	if(!n) {
#ifndef USE_WINSOCK
		close(fd);
#else
		closesocket(fd);
#endif
		log_err("out of memory");
		return 0;
	}
	n->next = *list;
	*list = n;
	n->fd = fd;
	return 1;
}
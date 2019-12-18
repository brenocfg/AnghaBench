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
typedef  char* uid_t ;
struct timeval {scalar_t__ tv_sec; int tv_usec; } ;
struct sockaddr {scalar_t__ sa_family; int /*<<< orphan*/  sa_len; } ;
struct netconfig {int dummy; } ;
typedef  scalar_t__ rpcvers_t ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  CLGET_FD ; 
 scalar_t__ CLIENT_CACHE_LIFETIME ; 
 int CLIENT_CACHE_SIZE ; 
 int /*<<< orphan*/  CLSET_TIMEOUT ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int NI_MAXHOST ; 
 int /*<<< orphan*/  NI_NUMERICHOST ; 
 int /*<<< orphan*/  NLM_PROG ; 
 int /*<<< orphan*/  addrcmp (struct sockaddr*,struct sockaddr*) ; 
 int /*<<< orphan*/  bindresvport (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * clnt_cache_addr ; 
 size_t clnt_cache_next_to_use ; 
 int /*<<< orphan*/ ** clnt_cache_ptr ; 
 long* clnt_cache_time ; 
 scalar_t__* clnt_cache_vers ; 
 int /*<<< orphan*/  clnt_control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  clnt_destroy (int /*<<< orphan*/ *) ; 
 char* clnt_spcreateerror (char*) ; 
 int /*<<< orphan*/ * clnt_tp_create (char*,int /*<<< orphan*/ ,scalar_t__,struct netconfig*) ; 
 int debug_level ; 
 int /*<<< orphan*/  freenetconfigent (struct netconfig*) ; 
 char* gai_strerror (int) ; 
 char* geteuid () ; 
 int getnameinfo (struct sockaddr*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct netconfig* getnetconfigent (char const*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr*,int /*<<< orphan*/ ) ; 
 scalar_t__ seteuid (char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 

CLIENT *
get_client(struct sockaddr *host_addr, rpcvers_t vers)
{
	CLIENT *client;
	struct timeval retry_time, time_now;
	int error, i;
	const char *netid;
	struct netconfig *nconf;
	char host[NI_MAXHOST];
	uid_t old_euid;
	int clnt_fd;

	gettimeofday(&time_now, NULL);

	/*
	 * Search for the given client in the cache, zapping any expired
	 * entries that we happen to notice in passing.
	 */
	for (i = 0; i < CLIENT_CACHE_SIZE; i++) {
		client = clnt_cache_ptr[i];
		if (client && ((clnt_cache_time[i] + CLIENT_CACHE_LIFETIME)
		    < time_now.tv_sec)) {
			/* Cache entry has expired. */
			if (debug_level > 3)
				syslog(LOG_DEBUG, "Expired CLIENT* in cache");
			clnt_cache_time[i] = 0L;
			clnt_destroy(client);
			clnt_cache_ptr[i] = NULL;
			client = NULL;
		}
		if (client && !addrcmp((struct sockaddr *)&clnt_cache_addr[i],
		    host_addr) && clnt_cache_vers[i] == vers) {
			/* Found it! */
			if (debug_level > 3)
				syslog(LOG_DEBUG, "Found CLIENT* in cache");
			return (client);
		}
	}

	if (debug_level > 3)
		syslog(LOG_DEBUG, "CLIENT* not found in cache, creating");

	/* Not found in cache.  Free the next entry if it is in use. */
	if (clnt_cache_ptr[clnt_cache_next_to_use]) {
		clnt_destroy(clnt_cache_ptr[clnt_cache_next_to_use]);
		clnt_cache_ptr[clnt_cache_next_to_use] = NULL;
	}

	/*
	 * Need a host string for clnt_tp_create. Use NI_NUMERICHOST
	 * to avoid DNS lookups.
	 */
	error = getnameinfo(host_addr, host_addr->sa_len, host, sizeof host,
			    NULL, 0, NI_NUMERICHOST);
	if (error != 0) {
		syslog(LOG_ERR, "unable to get name string for caller: %s",
		       gai_strerror(error));
		return NULL;
	}

#if 1
	if (host_addr->sa_family == AF_INET6)
		netid = "udp6";
	else
		netid = "udp";
#else 
	if (host_addr->sa_family == AF_INET6)
		netid = "tcp6";
	else
		netid = "tcp";
#endif
	nconf = getnetconfigent(netid);
	if (nconf == NULL) {
		syslog(LOG_ERR, "could not get netconfig info for '%s': "
				"no /etc/netconfig file?", netid);
		return NULL;
	}

	client = clnt_tp_create(host, NLM_PROG, vers, nconf);
	freenetconfigent(nconf);

	if (!client) {
		syslog(LOG_ERR, "%s", clnt_spcreateerror("clntudp_create"));
		syslog(LOG_ERR, "Unable to return result to %s", host);
		return NULL;
	}

	/* Get the FD of the client, for bindresvport. */ 
	clnt_control(client, CLGET_FD, &clnt_fd);

	/* Regain root privileges, for bindresvport. */
	old_euid = geteuid();
	if (seteuid(0) != 0) {
		syslog(LOG_ERR, "seteuid(0) failed");
		return NULL;
	}

	/*
	 * Bind the client FD to a reserved port.
	 * Some NFS servers reject any NLM request from a non-reserved port. 
	 */ 
	bindresvport(clnt_fd, NULL);

	/* Drop root privileges again. */
	if (seteuid(old_euid) != 0) {
		syslog(LOG_ERR, "seteuid(%d) failed", old_euid);
		return NULL;
	}

	/* Success - update the cache entry */
	clnt_cache_ptr[clnt_cache_next_to_use] = client;
	memcpy(&clnt_cache_addr[clnt_cache_next_to_use], host_addr,
	    host_addr->sa_len);
	clnt_cache_vers[clnt_cache_next_to_use] = vers;
	clnt_cache_time[clnt_cache_next_to_use] = time_now.tv_sec;
	if (++clnt_cache_next_to_use >= CLIENT_CACHE_SIZE)
		clnt_cache_next_to_use = 0;

	/*
	 * Disable the default timeout, so we can specify our own in calls
	 * to clnt_call().  (Note that the timeout is a different concept
	 * from the retry period set in clnt_udp_create() above.)
	 */
	retry_time.tv_sec = -1;
	retry_time.tv_usec = -1;
	clnt_control(client, CLSET_TIMEOUT, (char *)&retry_time);

	if (debug_level > 3)
		syslog(LOG_DEBUG, "Created CLIENT* for %s", host);
	return client;
}
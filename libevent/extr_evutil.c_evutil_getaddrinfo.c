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
struct hostent_data {scalar_t__ ai_family; int ai_flags; int /*<<< orphan*/  ai_socktype; } ;
struct hostent {scalar_t__ h_addrtype; scalar_t__ h_length; } ;
struct evutil_addrinfo {scalar_t__ ai_family; int ai_flags; int /*<<< orphan*/  ai_socktype; } ;
typedef  int /*<<< orphan*/  hints ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ALL_NATIVE_AI_FLAGS ; 
 int ALL_NONNATIVE_AI_FLAGS ; 
 int EVUTIL_AI_ADDRCONFIG ; 
 int EVUTIL_AI_NUMERICSERV ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int EVUTIL_EAI_AGAIN ; 
 int EVUTIL_EAI_FAIL ; 
 int EVUTIL_EAI_FAMILY ; 
 int EVUTIL_EAI_MEMORY ; 
 int EVUTIL_EAI_NEED_RESOLVE ; 
 int EVUTIL_EAI_NODATA ; 
 int EVUTIL_EAI_NONAME ; 
#define  HOST_NOT_FOUND 132 
#define  NO_ADDRESS 131 
#define  NO_DATA 130 
#define  NO_RECOVERY 129 
 scalar_t__ PF_INET ; 
 scalar_t__ PF_INET6 ; 
 scalar_t__ PF_UNSPEC ; 
#define  TRY_AGAIN 128 
 int WSAGetLastError () ; 
 struct hostent_data* addrinfo_from_hostent (struct hostent*,int,struct hostent_data*) ; 
 int /*<<< orphan*/  apply_numeric_port_hack (int,struct hostent_data**) ; 
 scalar_t__ apply_socktype_protocol_hack (struct hostent_data*) ; 
 int /*<<< orphan*/  evutil_adjust_hints_for_addrconfig_ (struct hostent_data*) ; 
 int /*<<< orphan*/  evutil_freeaddrinfo (struct hostent_data*) ; 
 int evutil_getaddrinfo_common_ (char const*,char const*,struct hostent_data*,struct hostent_data**,int*) ; 
 int /*<<< orphan*/  evutil_getaddrinfo_infer_protocols (struct hostent_data*) ; 
 int getaddrinfo (char const*,char const*,struct hostent_data*,struct hostent_data**) ; 
 struct hostent* gethostbyname (char const*) ; 
 int gethostbyname_r (char const*,struct hostent*,...) ; 
 int h_errno ; 
 int /*<<< orphan*/  memcpy (struct hostent_data*,struct hostent_data const*,int) ; 
 int /*<<< orphan*/  memset (struct hostent_data*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ need_numeric_port_hack () ; 
 scalar_t__ need_socktype_protocol_hack () ; 
 int parse_numeric_servname (char const*) ; 

int
evutil_getaddrinfo(const char *nodename, const char *servname,
    const struct evutil_addrinfo *hints_in, struct evutil_addrinfo **res)
{
#ifdef USE_NATIVE_GETADDRINFO
	struct evutil_addrinfo hints;
	int portnum=-1, need_np_hack, err;

	if (hints_in) {
		memcpy(&hints, hints_in, sizeof(hints));
	} else {
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = PF_UNSPEC;
	}

#ifndef AI_ADDRCONFIG
	/* Not every system has AI_ADDRCONFIG, so fake it. */
	if (hints.ai_family == PF_UNSPEC &&
	    (hints.ai_flags & EVUTIL_AI_ADDRCONFIG)) {
		evutil_adjust_hints_for_addrconfig_(&hints);
	}
#endif

#ifndef AI_NUMERICSERV
	/* Not every system has AI_NUMERICSERV, so fake it. */
	if (hints.ai_flags & EVUTIL_AI_NUMERICSERV) {
		if (servname && parse_numeric_servname(servname)<0)
			return EVUTIL_EAI_NONAME;
	}
#endif

	/* Enough operating systems handle enough common non-resolve
	 * cases here weirdly enough that we are better off just
	 * overriding them.  For example:
	 *
	 * - Windows doesn't like to infer the protocol from the
	 *   socket type, or fill in socket or protocol types much at
	 *   all.  It also seems to do its own broken implicit
	 *   always-on version of AI_ADDRCONFIG that keeps it from
	 *   ever resolving even a literal IPv6 address when
	 *   ai_addrtype is PF_UNSPEC.
	 */
#ifdef _WIN32
	{
		int tmp_port;
		err = evutil_getaddrinfo_common_(nodename,servname,&hints,
		    res, &tmp_port);
		if (err == 0 ||
		    err == EVUTIL_EAI_MEMORY ||
		    err == EVUTIL_EAI_NONAME)
			return err;
		/* If we make it here, the system getaddrinfo can
		 * have a crack at it. */
	}
#endif

	/* See documentation for need_numeric_port_hack above.*/
	need_np_hack = need_numeric_port_hack() && servname && !hints.ai_socktype
	    && ((portnum=parse_numeric_servname(servname)) >= 0);
	if (need_np_hack) {
		if (!nodename)
			return evutil_getaddrinfo_common_(
				NULL,servname,&hints, res, &portnum);
		servname = NULL;
	}

	if (need_socktype_protocol_hack()) {
		evutil_getaddrinfo_infer_protocols(&hints);
	}

	/* Make sure that we didn't actually steal any AI_FLAGS values that
	 * the system is using.  (This is a constant expression, and should ge
	 * optimized out.)
	 *
	 * XXXX Turn this into a compile-time failure rather than a run-time
	 * failure.
	 */
	EVUTIL_ASSERT((ALL_NONNATIVE_AI_FLAGS & ALL_NATIVE_AI_FLAGS) == 0);

	/* Clear any flags that only libevent understands. */
	hints.ai_flags &= ~ALL_NONNATIVE_AI_FLAGS;

	err = getaddrinfo(nodename, servname, &hints, res);
	if (need_np_hack)
		apply_numeric_port_hack(portnum, res);

	if (need_socktype_protocol_hack()) {
		if (apply_socktype_protocol_hack(*res) < 0) {
			evutil_freeaddrinfo(*res);
			*res = NULL;
			return EVUTIL_EAI_MEMORY;
		}
	}
	return err;
#else
	int port=0, err;
	struct hostent *ent = NULL;
	struct evutil_addrinfo hints;

	if (hints_in) {
		memcpy(&hints, hints_in, sizeof(hints));
	} else {
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = PF_UNSPEC;
	}

	evutil_adjust_hints_for_addrconfig_(&hints);

	err = evutil_getaddrinfo_common_(nodename, servname, &hints, res, &port);
	if (err != EVUTIL_EAI_NEED_RESOLVE) {
		/* We either succeeded or failed.  No need to continue */
		return err;
	}

	err = 0;
	/* Use any of the various gethostbyname_r variants as available. */
	{
#ifdef EVENT__HAVE_GETHOSTBYNAME_R_6_ARG
		/* This one is what glibc provides. */
		char buf[2048];
		struct hostent hostent;
		int r;
		r = gethostbyname_r(nodename, &hostent, buf, sizeof(buf), &ent,
		    &err);
#elif defined(EVENT__HAVE_GETHOSTBYNAME_R_5_ARG)
		char buf[2048];
		struct hostent hostent;
		ent = gethostbyname_r(nodename, &hostent, buf, sizeof(buf),
		    &err);
#elif defined(EVENT__HAVE_GETHOSTBYNAME_R_3_ARG)
		struct hostent_data data;
		struct hostent hostent;
		memset(&data, 0, sizeof(data));
		err = gethostbyname_r(nodename, &hostent, &data);
		ent = err ? NULL : &hostent;
#else
		/* fall back to gethostbyname. */
		/* XXXX This needs a lock everywhere but Windows. */
		ent = gethostbyname(nodename);
#ifdef _WIN32
		err = WSAGetLastError();
#else
		err = h_errno;
#endif
#endif

		/* Now we have either ent or err set. */
		if (!ent) {
			/* XXX is this right for windows ? */
			switch (err) {
			case TRY_AGAIN:
				return EVUTIL_EAI_AGAIN;
			case NO_RECOVERY:
			default:
				return EVUTIL_EAI_FAIL;
			case HOST_NOT_FOUND:
				return EVUTIL_EAI_NONAME;
			case NO_ADDRESS:
#if NO_DATA != NO_ADDRESS
			case NO_DATA:
#endif
				return EVUTIL_EAI_NODATA;
			}
		}

		if (ent->h_addrtype != hints.ai_family &&
		    hints.ai_family != PF_UNSPEC) {
			/* This wasn't the type we were hoping for.  Too bad
			 * we never had a chance to ask gethostbyname for what
			 * we wanted. */
			return EVUTIL_EAI_NONAME;
		}

		/* Make sure we got _some_ answers. */
		if (ent->h_length == 0)
			return EVUTIL_EAI_NODATA;

		/* If we got an address type we don't know how to make a
		   sockaddr for, give up. */
		if (ent->h_addrtype != PF_INET && ent->h_addrtype != PF_INET6)
			return EVUTIL_EAI_FAMILY;

		*res = addrinfo_from_hostent(ent, port, &hints);
		if (! *res)
			return EVUTIL_EAI_MEMORY;
	}

	return 0;
#endif
}
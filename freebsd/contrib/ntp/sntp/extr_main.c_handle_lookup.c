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
struct dns_ctx {char* name; int flags; int key_id; int /*<<< orphan*/ * key; int /*<<< orphan*/  timeout; } ;
struct addrinfo {int ai_flags; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;

/* Variables and functions */
 int AI_CANONNAME ; 
 int /*<<< orphan*/  AUTHENTICATION ; 
 scalar_t__ ENABLED_OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  KEYFILE ; 
 char* OPT_ARG (int /*<<< orphan*/ ) ; 
 int OPT_VALUE_AUTHENTICATION ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  TRACE (int,char*) ; 
 int /*<<< orphan*/  ZERO (struct addrinfo) ; 
 int Z_AI_NUMERICSERV ; 
 int /*<<< orphan*/  ai_fam_pref ; 
 struct dns_ctx* emalloc_zero (size_t) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,char*) ; 
 int /*<<< orphan*/  get_key (int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  getaddrinfo_sometime (char const*,char*,struct addrinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dns_ctx*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  n_pending_dns ; 
 char* progname ; 
 int /*<<< orphan*/  response_tv ; 
 int /*<<< orphan*/  sntp_name_resolved ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char const*) ; 

void
handle_lookup(
	const char *name,
	int flags
	)
{
	struct addrinfo	hints;	/* Local copy is OK */
	struct dns_ctx *ctx;
	char *		name_copy;
	size_t		name_sz;
	size_t		octets;

	TRACE(1, ("handle_lookup(%s,%#x)\n", name, flags));

	ZERO(hints);
	hints.ai_family = ai_fam_pref;
	hints.ai_flags = AI_CANONNAME | Z_AI_NUMERICSERV;
	/*
	** Unless we specify a socktype, we'll get at least two
	** entries for each address: one for TCP and one for
	** UDP. That's not what we want.
	*/
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;

	name_sz = 1 + strlen(name);
	octets = sizeof(*ctx) + name_sz;	// Space for a ctx and the name
	ctx = emalloc_zero(octets);		// ctx at ctx[0]
	name_copy = (char *)(ctx + 1);		// Put the name at ctx[1]
	memcpy(name_copy, name, name_sz);	// copy the name to ctx[1]
	ctx->name = name_copy;			// point to it...
	ctx->flags = flags;
	ctx->timeout = response_tv;
	ctx->key = NULL;

	/* The following should arguably be passed in... */
	if (ENABLED_OPT(AUTHENTICATION)) {
		ctx->key_id = OPT_VALUE_AUTHENTICATION;
		get_key(ctx->key_id, &ctx->key);
		if (NULL == ctx->key) {
			fprintf(stderr, "%s: Authentication with keyID %d requested, but no matching keyID found in <%s>!\n",
				progname, ctx->key_id, OPT_ARG(KEYFILE));
			exit(1);
		}
	} else {
		ctx->key_id = -1;
	}

	++n_pending_dns;
	getaddrinfo_sometime(name, "123", &hints, 0,
			     &sntp_name_resolved, ctx);
}
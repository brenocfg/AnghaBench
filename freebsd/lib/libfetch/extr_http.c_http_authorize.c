#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct url {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  password; int /*<<< orphan*/  user; scalar_t__ scheme; } ;
typedef  TYPE_1__ http_auth_params_t ;
struct TYPE_9__ {int count; TYPE_3__** challenges; } ;
typedef  TYPE_2__ http_auth_challenges_t ;
struct TYPE_10__ {scalar_t__ scheme; } ;
typedef  TYPE_3__ http_auth_challenge_t ;
typedef  int /*<<< orphan*/  conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGF (char*) ; 
 scalar_t__ HTTPAS_DIGEST ; 
 int http_basic_auth (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int http_digest_auth (int /*<<< orphan*/ *,char const*,TYPE_3__*,TYPE_1__*,struct url*) ; 
 scalar_t__ strcasecmp (scalar_t__,char*) ; 

__attribute__((used)) static int
http_authorize(conn_t *conn, const char *hdr, http_auth_challenges_t *cs,
	       http_auth_params_t *parms, struct url *url)
{
	http_auth_challenge_t *digest = NULL;
	int i;

	/* If user or pass are null we're not happy */
	if (!parms->user || !parms->password) {
		DEBUGF("NULL usr or pass\n");
		return (-1);
	}

	/* Look for a Digest */
	for (i = 0; i < cs->count; i++) {
		if (cs->challenges[i]->scheme == HTTPAS_DIGEST)
			digest = cs->challenges[i];
	}

	/* Error if "Digest" was specified and there is no Digest challenge */
	if (!digest &&
	    (parms->scheme && strcasecmp(parms->scheme, "digest") == 0)) {
		DEBUGF("Digest auth in env, not supported by peer\n");
		return (-1);
	}
	/*
	 * If "basic" was specified in the environment, or there is no Digest
	 * challenge, do the basic thing. Don't need a challenge for this,
	 * so no need to check basic!=NULL
	 */
	if (!digest ||
	    (parms->scheme && strcasecmp(parms->scheme, "basic") == 0))
		return (http_basic_auth(conn,hdr,parms->user,parms->password));

	/* Else, prefer digest. We just checked that it's not NULL */
	return (http_digest_auth(conn, hdr, digest, parms, url));
}
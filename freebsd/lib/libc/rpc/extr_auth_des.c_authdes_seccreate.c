#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_3__ {char* n_bytes; scalar_t__ n_len; } ;
typedef  TYPE_1__ netobj ;
typedef  int /*<<< orphan*/  des_block ;
typedef  int /*<<< orphan*/  AUTH ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/ * authdes_pk_seccreate (char const*,TYPE_1__*,scalar_t__ const,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getpublickey (char const*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char const*) ; 

AUTH *
authdes_seccreate(const char *servername, const u_int win,
	const char *timehost, const des_block *ckey)
{
	u_char  pkey_data[1024];
	netobj  pkey;
	AUTH    *dummy;

	if (! getpublickey(servername, (char *) pkey_data)) {
		syslog(LOG_ERR,
		    "authdes_seccreate: no public key found for %s",
		    servername);
		return (NULL);
	}

	pkey.n_bytes = (char *) pkey_data;
	pkey.n_len = (u_int)strlen((char *)pkey_data) + 1;
	dummy = authdes_pk_seccreate(servername, &pkey, win, timehost,
	    ckey, NULL);
	return (dummy);
}
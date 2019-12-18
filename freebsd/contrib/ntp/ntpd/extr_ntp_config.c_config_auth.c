#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  scalar_t__ u_char ;
typedef  void* keyid_t ;
struct TYPE_10__ {int revoke; int /*<<< orphan*/  trusted_key_list; scalar_t__ request_key; scalar_t__ control_key; scalar_t__ keys; scalar_t__ cryptosw; scalar_t__ ntp_signd_socket; scalar_t__ keysdir; int /*<<< orphan*/  crypto_cmd_list; } ;
struct TYPE_11__ {TYPE_3__ auth; } ;
typedef  TYPE_4__ config_tree ;
struct TYPE_8__ {int first; int last; } ;
struct TYPE_9__ {int i; TYPE_1__ r; int /*<<< orphan*/  s; } ;
struct TYPE_12__ {int attr; scalar_t__ type; TYPE_2__ value; struct TYPE_12__* link; } ;
typedef  TYPE_5__ attr_val ;

/* Variables and functions */
 int CRYPTO_CONF_IDENT ; 
 int CRYPTO_CONF_NID ; 
 int CRYPTO_CONF_PRIV ; 
 int CRYPTO_CONF_PW ; 
 int CRYPTO_CONF_RAND ; 
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 TYPE_5__* HEAD_PFIFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int NTP_MAXKEY ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  TRUE ; 
#define  T_Digest 132 
#define  T_Host 131 
#define  T_Ident 130 
 scalar_t__ T_Integer ; 
 scalar_t__ T_Intrange ; 
#define  T_Pw 129 
#define  T_Randfile 128 
 int /*<<< orphan*/  auth_prealloc_symkeys (int) ; 
 int /*<<< orphan*/  authtrust (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_config (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_setup () ; 
 int cryptosw ; 
 void* ctl_auth_keyid ; 
 scalar_t__ default_keysdir ; 
 scalar_t__ default_ntp_signd_socket ; 
 scalar_t__ estrdup (scalar_t__) ; 
 int /*<<< orphan*/  fatal_error (char*,int) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  getauthkeys (scalar_t__) ; 
 void* info_auth_keyid ; 
 scalar_t__ keysdir ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ ntp_signd_socket ; 
 scalar_t__ sys_revoke ; 

__attribute__((used)) static void
config_auth(
	config_tree *ptree
	)
{
	attr_val *	my_val;
	int		first;
	int		last;
	int		i;
	int		count;
#ifdef AUTOKEY
	int		item;
#endif

	/* Crypto Command */
#ifdef AUTOKEY
	my_val = HEAD_PFIFO(ptree->auth.crypto_cmd_list);
	for (; my_val != NULL; my_val = my_val->link) {
		switch (my_val->attr) {

		default:
			fatal_error("config_auth: attr-token=%d", my_val->attr);

		case T_Host:
			item = CRYPTO_CONF_PRIV;
			break;

		case T_Ident:
			item = CRYPTO_CONF_IDENT;
			break;

		case T_Pw:
			item = CRYPTO_CONF_PW;
			break;

		case T_Randfile:
			item = CRYPTO_CONF_RAND;
			break;

		case T_Digest:
			item = CRYPTO_CONF_NID;
			break;
		}
		crypto_config(item, my_val->value.s);
	}
#endif	/* AUTOKEY */

	/* Keysdir Command */
	if (ptree->auth.keysdir) {
		if (keysdir != default_keysdir)
			free(keysdir);
		keysdir = estrdup(ptree->auth.keysdir);
	}


	/* ntp_signd_socket Command */
	if (ptree->auth.ntp_signd_socket) {
		if (ntp_signd_socket != default_ntp_signd_socket)
			free(ntp_signd_socket);
		ntp_signd_socket = estrdup(ptree->auth.ntp_signd_socket);
	}

#ifdef AUTOKEY
	if (ptree->auth.cryptosw && !cryptosw) {
		crypto_setup();
		cryptosw = 1;
	}
#endif	/* AUTOKEY */

	/*
	 * Count the number of trusted keys to preallocate storage and
	 * size the hash table.
	 */
	count = 0;
	my_val = HEAD_PFIFO(ptree->auth.trusted_key_list);
	for (; my_val != NULL; my_val = my_val->link) {
		if (T_Integer == my_val->type) {
			first = my_val->value.i;
			if (first > 1 && first <= NTP_MAXKEY)
				count++;
		} else {
			REQUIRE(T_Intrange == my_val->type);
			first = my_val->value.r.first;
			last = my_val->value.r.last;
			if (!(first > last || first < 1 ||
			    last > NTP_MAXKEY)) {
				count += 1 + last - first;
			}
		}
	}
	auth_prealloc_symkeys(count);

	/* Keys Command */
	if (ptree->auth.keys)
		getauthkeys(ptree->auth.keys);

	/* Control Key Command */
	if (ptree->auth.control_key)
		ctl_auth_keyid = (keyid_t)ptree->auth.control_key;

	/* Requested Key Command */
	if (ptree->auth.request_key) {
		DPRINTF(4, ("set info_auth_keyid to %08lx\n",
			    (u_long) ptree->auth.request_key));
		info_auth_keyid = (keyid_t)ptree->auth.request_key;
	}

	/* Trusted Key Command */
	my_val = HEAD_PFIFO(ptree->auth.trusted_key_list);
	for (; my_val != NULL; my_val = my_val->link) {
		if (T_Integer == my_val->type) {
			first = my_val->value.i;
			if (first >= 1 && first <= NTP_MAXKEY) {
				authtrust(first, TRUE);
			} else {
				msyslog(LOG_NOTICE,
					"Ignoring invalid trustedkey %d, min 1 max %d.",
					first, NTP_MAXKEY);
			}
		} else {
			first = my_val->value.r.first;
			last = my_val->value.r.last;
			if (first > last || first < 1 ||
			    last > NTP_MAXKEY) {
				msyslog(LOG_NOTICE,
					"Ignoring invalid trustedkey range %d ... %d, min 1 max %d.",
					first, last, NTP_MAXKEY);
			} else {
				for (i = first; i <= last; i++) {
					authtrust(i, TRUE);
				}
			}
		}
	}

#ifdef AUTOKEY
	/* crypto revoke command */
	if (ptree->auth.revoke > 2 && ptree->auth.revoke < 32)
		sys_revoke = (u_char)ptree->auth.revoke;
	else if (ptree->auth.revoke)
		msyslog(LOG_ERR,
			"'revoke' value %d ignored",
			ptree->auth.revoke);
#endif	/* AUTOKEY */
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
typedef  int mode_t ;
struct TYPE_7__ {int gateway_ports; int streamlocal_bind_mask; int streamlocal_bind_unlink; } ;
struct TYPE_8__ {int use_pam; scalar_t__ num_host_key_files; scalar_t__ num_ports; int address_family; int login_grace_time; scalar_t__ permit_root_login; int ignore_rhosts; int ignore_user_known_hosts; int print_motd; int print_lastlog; int x11_forwarding; int x11_display_offset; int x11_use_localhost; int permit_tty; int permit_user_rc; int strict_modes; int tcp_keep_alive; scalar_t__ log_facility; scalar_t__ log_level; int hostbased_authentication; int hostbased_uses_name_from_packet_only; int pubkey_authentication; int kerberos_authentication; int kerberos_or_local_passwd; int kerberos_ticket_cleanup; int kerberos_get_afs_token; int gss_authentication; int gss_cleanup_creds; int gss_strict_acceptor; int password_authentication; int kbd_interactive_authentication; int challenge_response_authentication; int permit_empty_passwd; int permit_user_env; int compression; int rekey_limit; int rekey_interval; int allow_tcp_forwarding; int allow_streamlocal_forwarding; int allow_agent_forwarding; int max_startups; int max_startups_rate; int max_startups_begin; int max_authtries; int max_sessions; int use_dns; int client_alive_interval; int client_alive_count_max; scalar_t__ num_authkeys_files; int permit_tun; int ip_qos_interactive; int ip_qos_bulk; int fingerprint_hash; int disable_forwarding; int expose_userauth_info; int use_blacklist; size_t num_host_cert_files; int num_auth_methods; int /*<<< orphan*/ ** auth_methods; int /*<<< orphan*/ ** host_cert_files; int /*<<< orphan*/ ** host_key_files; int /*<<< orphan*/ * routing_domain; int /*<<< orphan*/ * chroot_directory; int /*<<< orphan*/ * adm_forced_command; int /*<<< orphan*/ * authorized_principals_file; int /*<<< orphan*/ * revoked_keys_file; int /*<<< orphan*/ * trusted_user_ca_keys; int /*<<< orphan*/ * banner; int /*<<< orphan*/ * xauth_location; int /*<<< orphan*/ * pid_file; TYPE_1__ fwd_opts; int /*<<< orphan*/ * version_addendum; int /*<<< orphan*/  authorized_keys_files; int /*<<< orphan*/ * permit_user_env_whitelist; int /*<<< orphan*/ * listen_addrs; int /*<<< orphan*/ * ports; } ;
typedef  TYPE_2__ ServerOptions ;

/* Variables and functions */
 int AF_UNSPEC ; 
 int /*<<< orphan*/  CLEAR_ON_NONE (int /*<<< orphan*/ *) ; 
 int COMP_DELAYED ; 
 int DEFAULT_AUTH_FAIL_MAX ; 
 int DEFAULT_SESSIONS_MAX ; 
 void* FORWARD_ALLOW ; 
 int IPTOS_DSCP_AF21 ; 
 int IPTOS_DSCP_CS1 ; 
 scalar_t__ PERMIT_NO ; 
 scalar_t__ PERMIT_NOT_SET ; 
 int PRIVSEP_ON ; 
 int /*<<< orphan*/  SSH_DEFAULT_PORT ; 
 int SSH_FP_HASH_DEFAULT ; 
 int SSH_TUNMODE_NO ; 
 int /*<<< orphan*/  SSH_VERSION_FREEBSD ; 
 scalar_t__ SYSLOG_FACILITY_AUTH ; 
 scalar_t__ SYSLOG_FACILITY_NOT_SET ; 
 scalar_t__ SYSLOG_LEVEL_INFO ; 
 scalar_t__ SYSLOG_LEVEL_NOT_SET ; 
 int /*<<< orphan*/  _PATH_HOST_DSA_KEY_FILE ; 
 int /*<<< orphan*/  _PATH_HOST_ECDSA_KEY_FILE ; 
 int /*<<< orphan*/  _PATH_HOST_ED25519_KEY_FILE ; 
 int /*<<< orphan*/  _PATH_HOST_RSA_KEY_FILE ; 
 int /*<<< orphan*/  _PATH_HOST_XMSS_KEY_FILE ; 
 int /*<<< orphan*/  _PATH_SSH_DAEMON_PID_FILE ; 
 int /*<<< orphan*/  _PATH_SSH_USER_PERMITTED_KEYS ; 
 int /*<<< orphan*/  _PATH_SSH_USER_PERMITTED_KEYS2 ; 
 int /*<<< orphan*/  _PATH_XAUTH ; 
 int /*<<< orphan*/  add_listen_addr (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_append (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assemble_algorithms (TYPE_2__*) ; 
 int /*<<< orphan*/  defaultkey ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  servconf_add_hostkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 int use_privsep ; 
 void* xstrdup (int /*<<< orphan*/ ) ; 

void
fill_default_server_options(ServerOptions *options)
{
	u_int i;

	/* Portable-specific options */
	if (options->use_pam == -1)
		options->use_pam = 1;

	/* Standard Options */
	if (options->num_host_key_files == 0) {
		/* fill default hostkeys for protocols */
		servconf_add_hostkey(defaultkey, 0, options,
		    _PATH_HOST_RSA_KEY_FILE);
		servconf_add_hostkey(defaultkey, 0, options,
		    _PATH_HOST_DSA_KEY_FILE);
#ifdef OPENSSL_HAS_ECC
		servconf_add_hostkey(defaultkey, 0, options,
		    _PATH_HOST_ECDSA_KEY_FILE);
#endif
		servconf_add_hostkey(defaultkey, 0, options,
		    _PATH_HOST_ED25519_KEY_FILE);
#ifdef WITH_XMSS
		servconf_add_hostkey(defaultkey, 0, options,
		    _PATH_HOST_XMSS_KEY_FILE);
#endif /* WITH_XMSS */
	}
	if (options->num_host_key_files == 0)
		fatal("No host key files found");
	/* No certificates by default */
	if (options->num_ports == 0)
		options->ports[options->num_ports++] = SSH_DEFAULT_PORT;
	if (options->address_family == -1)
		options->address_family = AF_UNSPEC;
	if (options->listen_addrs == NULL)
		add_listen_addr(options, NULL, NULL, 0);
	if (options->pid_file == NULL)
		options->pid_file = xstrdup(_PATH_SSH_DAEMON_PID_FILE);
	if (options->login_grace_time == -1)
		options->login_grace_time = 120;
	if (options->permit_root_login == PERMIT_NOT_SET)
		options->permit_root_login = PERMIT_NO;
	if (options->ignore_rhosts == -1)
		options->ignore_rhosts = 1;
	if (options->ignore_user_known_hosts == -1)
		options->ignore_user_known_hosts = 0;
	if (options->print_motd == -1)
		options->print_motd = 1;
	if (options->print_lastlog == -1)
		options->print_lastlog = 1;
	if (options->x11_forwarding == -1)
		options->x11_forwarding = 1;
	if (options->x11_display_offset == -1)
		options->x11_display_offset = 10;
	if (options->x11_use_localhost == -1)
		options->x11_use_localhost = 1;
	if (options->xauth_location == NULL)
		options->xauth_location = xstrdup(_PATH_XAUTH);
	if (options->permit_tty == -1)
		options->permit_tty = 1;
	if (options->permit_user_rc == -1)
		options->permit_user_rc = 1;
	if (options->strict_modes == -1)
		options->strict_modes = 1;
	if (options->tcp_keep_alive == -1)
		options->tcp_keep_alive = 1;
	if (options->log_facility == SYSLOG_FACILITY_NOT_SET)
		options->log_facility = SYSLOG_FACILITY_AUTH;
	if (options->log_level == SYSLOG_LEVEL_NOT_SET)
		options->log_level = SYSLOG_LEVEL_INFO;
	if (options->hostbased_authentication == -1)
		options->hostbased_authentication = 0;
	if (options->hostbased_uses_name_from_packet_only == -1)
		options->hostbased_uses_name_from_packet_only = 0;
	if (options->pubkey_authentication == -1)
		options->pubkey_authentication = 1;
	if (options->kerberos_authentication == -1)
		options->kerberos_authentication = 0;
	if (options->kerberos_or_local_passwd == -1)
		options->kerberos_or_local_passwd = 1;
	if (options->kerberos_ticket_cleanup == -1)
		options->kerberos_ticket_cleanup = 1;
	if (options->kerberos_get_afs_token == -1)
		options->kerberos_get_afs_token = 0;
	if (options->gss_authentication == -1)
		options->gss_authentication = 0;
	if (options->gss_cleanup_creds == -1)
		options->gss_cleanup_creds = 1;
	if (options->gss_strict_acceptor == -1)
		options->gss_strict_acceptor = 1;
	if (options->password_authentication == -1)
		options->password_authentication = 0;
	if (options->kbd_interactive_authentication == -1)
		options->kbd_interactive_authentication = 0;
	if (options->challenge_response_authentication == -1)
		options->challenge_response_authentication = 1;
	if (options->permit_empty_passwd == -1)
		options->permit_empty_passwd = 0;
	if (options->permit_user_env == -1) {
		options->permit_user_env = 0;
		options->permit_user_env_whitelist = NULL;
	}
	if (options->compression == -1)
		options->compression = COMP_DELAYED;
	if (options->rekey_limit == -1)
		options->rekey_limit = 0;
	if (options->rekey_interval == -1)
		options->rekey_interval = 0;
	if (options->allow_tcp_forwarding == -1)
		options->allow_tcp_forwarding = FORWARD_ALLOW;
	if (options->allow_streamlocal_forwarding == -1)
		options->allow_streamlocal_forwarding = FORWARD_ALLOW;
	if (options->allow_agent_forwarding == -1)
		options->allow_agent_forwarding = 1;
	if (options->fwd_opts.gateway_ports == -1)
		options->fwd_opts.gateway_ports = 0;
	if (options->max_startups == -1)
		options->max_startups = 100;
	if (options->max_startups_rate == -1)
		options->max_startups_rate = 30;		/* 30% */
	if (options->max_startups_begin == -1)
		options->max_startups_begin = 10;
	if (options->max_authtries == -1)
		options->max_authtries = DEFAULT_AUTH_FAIL_MAX;
	if (options->max_sessions == -1)
		options->max_sessions = DEFAULT_SESSIONS_MAX;
	if (options->use_dns == -1)
		options->use_dns = 1;
	if (options->client_alive_interval == -1)
		options->client_alive_interval = 0;
	if (options->client_alive_count_max == -1)
		options->client_alive_count_max = 3;
	if (options->num_authkeys_files == 0) {
		array_append(defaultkey, 0, "AuthorizedKeysFiles",
		    &options->authorized_keys_files,
		    &options->num_authkeys_files,
		    _PATH_SSH_USER_PERMITTED_KEYS);
		array_append(defaultkey, 0, "AuthorizedKeysFiles",
		    &options->authorized_keys_files,
		    &options->num_authkeys_files,
		    _PATH_SSH_USER_PERMITTED_KEYS2);
	}
	if (options->permit_tun == -1)
		options->permit_tun = SSH_TUNMODE_NO;
	if (options->ip_qos_interactive == -1)
		options->ip_qos_interactive = IPTOS_DSCP_AF21;
	if (options->ip_qos_bulk == -1)
		options->ip_qos_bulk = IPTOS_DSCP_CS1;
	if (options->version_addendum == NULL)
		options->version_addendum = xstrdup(SSH_VERSION_FREEBSD);
	if (options->fwd_opts.streamlocal_bind_mask == (mode_t)-1)
		options->fwd_opts.streamlocal_bind_mask = 0177;
	if (options->fwd_opts.streamlocal_bind_unlink == -1)
		options->fwd_opts.streamlocal_bind_unlink = 0;
	if (options->fingerprint_hash == -1)
		options->fingerprint_hash = SSH_FP_HASH_DEFAULT;
	if (options->disable_forwarding == -1)
		options->disable_forwarding = 0;
	if (options->expose_userauth_info == -1)
		options->expose_userauth_info = 0;
	if (options->use_blacklist == -1)
		options->use_blacklist = 0;

	assemble_algorithms(options);

	/* Turn privilege separation and sandboxing on by default */
	if (use_privsep == -1)
		use_privsep = PRIVSEP_ON;

#define CLEAR_ON_NONE(v) \
	do { \
		if (option_clear_or_none(v)) { \
			free(v); \
			v = NULL; \
		} \
	} while(0)
	CLEAR_ON_NONE(options->pid_file);
	CLEAR_ON_NONE(options->xauth_location);
	CLEAR_ON_NONE(options->banner);
	CLEAR_ON_NONE(options->trusted_user_ca_keys);
	CLEAR_ON_NONE(options->revoked_keys_file);
	CLEAR_ON_NONE(options->authorized_principals_file);
	CLEAR_ON_NONE(options->adm_forced_command);
	CLEAR_ON_NONE(options->chroot_directory);
	CLEAR_ON_NONE(options->routing_domain);
	for (i = 0; i < options->num_host_key_files; i++)
		CLEAR_ON_NONE(options->host_key_files[i]);
	for (i = 0; i < options->num_host_cert_files; i++)
		CLEAR_ON_NONE(options->host_cert_files[i]);
#undef CLEAR_ON_NONE

	/* Similar handling for AuthenticationMethods=any */
	if (options->num_auth_methods == 1 &&
	    strcmp(options->auth_methods[0], "any") == 0) {
		free(options->auth_methods[0]);
		options->auth_methods[0] = NULL;
		options->num_auth_methods = 0;
	}

#ifndef HAVE_MMAP
	if (use_privsep && options->compression == 1) {
		error("This platform does not support both privilege "
		    "separation and compression");
		error("Compression disabled");
		options->compression = 0;
	}
#endif

}
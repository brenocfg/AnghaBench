#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mode_t ;
struct TYPE_5__ {int gateway_ports; int streamlocal_bind_unlink; scalar_t__ streamlocal_bind_mask; } ;
struct TYPE_6__ {int forward_agent; int forward_x11; int forward_x11_trusted; int forward_x11_timeout; int clear_forwardings; int exit_on_forward_failure; int pubkey_authentication; int challenge_response_authentication; int gss_authentication; int gss_deleg_creds; int password_authentication; int kbd_interactive_authentication; int hostbased_authentication; int batch_mode; int check_host_ip; int strict_host_key_checking; int compression; int tcp_keep_alive; int port; int address_family; int connection_attempts; int connection_timeout; int number_of_password_prompts; int jump_port; int escape_char; int enable_ssh_keysign; int no_host_authentication_for_localhost; int identities_only; int rekey_limit; int rekey_interval; int verify_host_key_dns; int server_alive_interval; int server_alive_count_max; int control_master; int control_persist; int hash_known_hosts; int tun_open; int tun_local; int tun_remote; int permit_local_command; int add_keys_to_agent; int visual_host_key; int ip_qos_interactive; int ip_qos_bulk; int request_tty; int proxy_use_fdpass; int canonicalize_max_dots; int canonicalize_fallback_local; int canonicalize_hostname; int fingerprint_hash; int update_hostkeys; int /*<<< orphan*/ * pubkey_key_types; int /*<<< orphan*/ * hostbased_key_types; int /*<<< orphan*/ * revoked_host_keys; scalar_t__ num_permitted_cnames; scalar_t__ num_canonical_domains; int /*<<< orphan*/ * ignored_unknown; int /*<<< orphan*/ * identity_agent; int /*<<< orphan*/ * remote_command; int /*<<< orphan*/ * local_command; scalar_t__ control_persist_timeout; int /*<<< orphan*/ * control_path; scalar_t__ num_setenv; int /*<<< orphan*/ * setenv; scalar_t__ num_send_env; int /*<<< orphan*/ * send_env; int /*<<< orphan*/ * pkcs11_provider; int /*<<< orphan*/ * bind_interface; int /*<<< orphan*/ * bind_address; int /*<<< orphan*/ * preferred_authentications; int /*<<< orphan*/  log_level; int /*<<< orphan*/  log_facility; scalar_t__ num_remote_forwards; int /*<<< orphan*/ * remote_forwards; scalar_t__ num_local_forwards; int /*<<< orphan*/ * local_forwards; scalar_t__ num_user_hostfiles; scalar_t__ num_system_hostfiles; int /*<<< orphan*/ * user; int /*<<< orphan*/ * jump_extra; int /*<<< orphan*/ * jump_host; int /*<<< orphan*/ * jump_user; int /*<<< orphan*/ * proxy_command; int /*<<< orphan*/ * host_key_alias; int /*<<< orphan*/ * hostname; scalar_t__ num_certificate_files; scalar_t__ num_identity_files; int /*<<< orphan*/ * hostkeyalgorithms; int /*<<< orphan*/ * kex_algorithms; int /*<<< orphan*/ * macs; int /*<<< orphan*/ * ciphers; int /*<<< orphan*/ * kbd_interactive_devices; TYPE_1__ fwd_opts; int /*<<< orphan*/ * xauth_location; scalar_t__ stdio_forward_port; int /*<<< orphan*/ * stdio_forward_host; int /*<<< orphan*/ * version_addendum; } ;
typedef  TYPE_2__ Options ;

/* Variables and functions */
 int /*<<< orphan*/  SYSLOG_FACILITY_NOT_SET ; 
 int /*<<< orphan*/  SYSLOG_LEVEL_NOT_SET ; 
 int /*<<< orphan*/  memset (TYPE_2__*,char,int) ; 

void
initialize_options(Options * options)
{
	memset(options, 'X', sizeof(*options));
	options->version_addendum = NULL;
	options->forward_agent = -1;
	options->forward_x11 = -1;
	options->forward_x11_trusted = -1;
	options->forward_x11_timeout = -1;
	options->stdio_forward_host = NULL;
	options->stdio_forward_port = 0;
	options->clear_forwardings = -1;
	options->exit_on_forward_failure = -1;
	options->xauth_location = NULL;
	options->fwd_opts.gateway_ports = -1;
	options->fwd_opts.streamlocal_bind_mask = (mode_t)-1;
	options->fwd_opts.streamlocal_bind_unlink = -1;
	options->pubkey_authentication = -1;
	options->challenge_response_authentication = -1;
	options->gss_authentication = -1;
	options->gss_deleg_creds = -1;
	options->password_authentication = -1;
	options->kbd_interactive_authentication = -1;
	options->kbd_interactive_devices = NULL;
	options->hostbased_authentication = -1;
	options->batch_mode = -1;
	options->check_host_ip = -1;
	options->strict_host_key_checking = -1;
	options->compression = -1;
	options->tcp_keep_alive = -1;
	options->port = -1;
	options->address_family = -1;
	options->connection_attempts = -1;
	options->connection_timeout = -1;
	options->number_of_password_prompts = -1;
	options->ciphers = NULL;
	options->macs = NULL;
	options->kex_algorithms = NULL;
	options->hostkeyalgorithms = NULL;
	options->num_identity_files = 0;
	options->num_certificate_files = 0;
	options->hostname = NULL;
	options->host_key_alias = NULL;
	options->proxy_command = NULL;
	options->jump_user = NULL;
	options->jump_host = NULL;
	options->jump_port = -1;
	options->jump_extra = NULL;
	options->user = NULL;
	options->escape_char = -1;
	options->num_system_hostfiles = 0;
	options->num_user_hostfiles = 0;
	options->local_forwards = NULL;
	options->num_local_forwards = 0;
	options->remote_forwards = NULL;
	options->num_remote_forwards = 0;
	options->log_facility = SYSLOG_FACILITY_NOT_SET;
	options->log_level = SYSLOG_LEVEL_NOT_SET;
	options->preferred_authentications = NULL;
	options->bind_address = NULL;
	options->bind_interface = NULL;
	options->pkcs11_provider = NULL;
	options->enable_ssh_keysign = - 1;
	options->no_host_authentication_for_localhost = - 1;
	options->identities_only = - 1;
	options->rekey_limit = - 1;
	options->rekey_interval = -1;
	options->verify_host_key_dns = -1;
	options->server_alive_interval = -1;
	options->server_alive_count_max = -1;
	options->send_env = NULL;
	options->num_send_env = 0;
	options->setenv = NULL;
	options->num_setenv = 0;
	options->control_path = NULL;
	options->control_master = -1;
	options->control_persist = -1;
	options->control_persist_timeout = 0;
	options->hash_known_hosts = -1;
	options->tun_open = -1;
	options->tun_local = -1;
	options->tun_remote = -1;
	options->local_command = NULL;
	options->permit_local_command = -1;
	options->remote_command = NULL;
	options->add_keys_to_agent = -1;
	options->identity_agent = NULL;
	options->visual_host_key = -1;
	options->ip_qos_interactive = -1;
	options->ip_qos_bulk = -1;
	options->request_tty = -1;
	options->proxy_use_fdpass = -1;
	options->ignored_unknown = NULL;
	options->num_canonical_domains = 0;
	options->num_permitted_cnames = 0;
	options->canonicalize_max_dots = -1;
	options->canonicalize_fallback_local = -1;
	options->canonicalize_hostname = -1;
	options->revoked_host_keys = NULL;
	options->fingerprint_hash = -1;
	options->update_hostkeys = -1;
	options->hostbased_key_types = NULL;
	options->pubkey_key_types = NULL;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  first; } ;
struct TYPE_3__ {int /*<<< orphan*/  first; } ;
struct config_file {struct config_file* cachedb_secret; struct config_file* cachedb_backend; int /*<<< orphan*/  ipsecmod_whitelist; struct config_file* ipsecmod_hook; int /*<<< orphan*/  ratelimit_below_domain; int /*<<< orphan*/  ratelimit_for_domain; struct config_file* dnstap_version; struct config_file* dnstap_identity; struct config_file* dnstap_socket_path; int /*<<< orphan*/  dns64_ignore_aaaa; struct config_file* dns64_prefix; struct config_file* control_cert_file; struct config_file* control_key_file; struct config_file* server_cert_file; struct config_file* server_key_file; TYPE_2__ control_ifs; int /*<<< orphan*/  acl_tag_datas; int /*<<< orphan*/  acl_tag_actions; int /*<<< orphan*/  respip_tags; int /*<<< orphan*/  acl_tags; int /*<<< orphan*/  local_zone_tags; int /*<<< orphan*/  num_tags; int /*<<< orphan*/  tagname; int /*<<< orphan*/  local_zone_overrides; int /*<<< orphan*/  local_data; int /*<<< orphan*/  local_zones_nodefault; int /*<<< orphan*/  local_zones; struct config_file* val_nsec3_key_iterations; int /*<<< orphan*/  tcp_connection_limits; int /*<<< orphan*/  acls; int /*<<< orphan*/  dlv_anchor_list; struct config_file* dlv_anchor_file; int /*<<< orphan*/  domain_insecure; int /*<<< orphan*/  trust_anchor_list; int /*<<< orphan*/  trusted_keys_file_list; int /*<<< orphan*/  trust_anchor_file_list; int /*<<< orphan*/  auto_trust_anchor_file_list; int /*<<< orphan*/  private_domain; int /*<<< orphan*/  private_address; int /*<<< orphan*/  caps_whitelist; struct config_file* python_script; struct config_file* outgoing_avail_ports; struct config_file* module_conf; struct config_file* version; struct config_file* identity; int /*<<< orphan*/  client_subnet_zone; int /*<<< orphan*/  client_subnet; int /*<<< orphan*/  root_hints; int /*<<< orphan*/  donotqueryaddrs; int /*<<< orphan*/  views; int /*<<< orphan*/  auths; int /*<<< orphan*/  forwards; int /*<<< orphan*/  stubs; int /*<<< orphan*/  num_out_ifs; int /*<<< orphan*/  out_ifs; int /*<<< orphan*/  num_ifs; int /*<<< orphan*/  ifs; struct config_file* log_identity; struct config_file* tls_ciphersuites; struct config_file* tls_ciphers; TYPE_1__ tls_session_ticket_keys; int /*<<< orphan*/  tls_additional_port; struct config_file* tls_cert_bundle; struct config_file* ssl_service_pem; struct config_file* ssl_service_key; struct config_file* target_fetch_policy; struct config_file* pidfile; struct config_file* logfile; struct config_file* directory; struct config_file* chrootdir; struct config_file* username; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_del_strarray (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_del_strbytelist (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_delauths (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_deldblstrlist (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_delstrlist (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_delstubs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_deltrplstrlist (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_delviews (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct config_file*) ; 

void 
config_delete(struct config_file* cfg)
{
	if(!cfg) return;
	free(cfg->username);
	free(cfg->chrootdir);
	free(cfg->directory);
	free(cfg->logfile);
	free(cfg->pidfile);
	free(cfg->target_fetch_policy);
	free(cfg->ssl_service_key);
	free(cfg->ssl_service_pem);
	free(cfg->tls_cert_bundle);
	config_delstrlist(cfg->tls_additional_port);
	config_delstrlist(cfg->tls_session_ticket_keys.first);
	free(cfg->tls_ciphers);
	free(cfg->tls_ciphersuites);
	free(cfg->log_identity);
	config_del_strarray(cfg->ifs, cfg->num_ifs);
	config_del_strarray(cfg->out_ifs, cfg->num_out_ifs);
	config_delstubs(cfg->stubs);
	config_delstubs(cfg->forwards);
	config_delauths(cfg->auths);
	config_delviews(cfg->views);
	config_delstrlist(cfg->donotqueryaddrs);
	config_delstrlist(cfg->root_hints);
#ifdef CLIENT_SUBNET
	config_delstrlist(cfg->client_subnet);
	config_delstrlist(cfg->client_subnet_zone);
#endif
	free(cfg->identity);
	free(cfg->version);
	free(cfg->module_conf);
	free(cfg->outgoing_avail_ports);
	free(cfg->python_script);
	config_delstrlist(cfg->caps_whitelist);
	config_delstrlist(cfg->private_address);
	config_delstrlist(cfg->private_domain);
	config_delstrlist(cfg->auto_trust_anchor_file_list);
	config_delstrlist(cfg->trust_anchor_file_list);
	config_delstrlist(cfg->trusted_keys_file_list);
	config_delstrlist(cfg->trust_anchor_list);
	config_delstrlist(cfg->domain_insecure);
	free(cfg->dlv_anchor_file);
	config_delstrlist(cfg->dlv_anchor_list);
	config_deldblstrlist(cfg->acls);
	config_deldblstrlist(cfg->tcp_connection_limits);
	free(cfg->val_nsec3_key_iterations);
	config_deldblstrlist(cfg->local_zones);
	config_delstrlist(cfg->local_zones_nodefault);
	config_delstrlist(cfg->local_data);
	config_deltrplstrlist(cfg->local_zone_overrides);
	config_del_strarray(cfg->tagname, cfg->num_tags);
	config_del_strbytelist(cfg->local_zone_tags);
	config_del_strbytelist(cfg->acl_tags);
	config_del_strbytelist(cfg->respip_tags);
	config_deltrplstrlist(cfg->acl_tag_actions);
	config_deltrplstrlist(cfg->acl_tag_datas);
	config_delstrlist(cfg->control_ifs.first);
	free(cfg->server_key_file);
	free(cfg->server_cert_file);
	free(cfg->control_key_file);
	free(cfg->control_cert_file);
	free(cfg->dns64_prefix);
	config_delstrlist(cfg->dns64_ignore_aaaa);
	free(cfg->dnstap_socket_path);
	free(cfg->dnstap_identity);
	free(cfg->dnstap_version);
	config_deldblstrlist(cfg->ratelimit_for_domain);
	config_deldblstrlist(cfg->ratelimit_below_domain);
#ifdef USE_IPSECMOD
	free(cfg->ipsecmod_hook);
	config_delstrlist(cfg->ipsecmod_whitelist);
#endif
#ifdef USE_CACHEDB
	free(cfg->cachedb_backend);
	free(cfg->cachedb_secret);
#endif
	free(cfg);
}
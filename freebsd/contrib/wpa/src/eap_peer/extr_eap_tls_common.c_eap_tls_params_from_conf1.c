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
struct tls_connection_params {int /*<<< orphan*/  ca_cert_id; int /*<<< orphan*/  cert_id; int /*<<< orphan*/  key_id; int /*<<< orphan*/  pin; int /*<<< orphan*/  engine_id; int /*<<< orphan*/  engine; int /*<<< orphan*/  domain_match; int /*<<< orphan*/  suffix_match; int /*<<< orphan*/  check_cert_subject; int /*<<< orphan*/  altsubject_match; int /*<<< orphan*/  subject_match; int /*<<< orphan*/  dh_file; int /*<<< orphan*/  private_key_passwd; int /*<<< orphan*/  private_key; int /*<<< orphan*/  client_cert; int /*<<< orphan*/  ca_path; int /*<<< orphan*/  ca_cert; } ;
struct eap_peer_config {int /*<<< orphan*/  phase1; int /*<<< orphan*/  ca_cert_id; int /*<<< orphan*/  cert_id; int /*<<< orphan*/  key_id; int /*<<< orphan*/  pin; int /*<<< orphan*/  engine_id; int /*<<< orphan*/  engine; int /*<<< orphan*/  domain_match; int /*<<< orphan*/  domain_suffix_match; int /*<<< orphan*/  check_cert_subject; int /*<<< orphan*/  altsubject_match; int /*<<< orphan*/  subject_match; int /*<<< orphan*/  dh_file; int /*<<< orphan*/  private_key_passwd; int /*<<< orphan*/  private_key; int /*<<< orphan*/  client_cert; int /*<<< orphan*/  ca_path; int /*<<< orphan*/  ca_cert; } ;

/* Variables and functions */
 int /*<<< orphan*/  eap_tls_params_flags (struct tls_connection_params*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eap_tls_params_from_conf1(struct tls_connection_params *params,
				      struct eap_peer_config *config)
{
	params->ca_cert = config->ca_cert;
	params->ca_path = config->ca_path;
	params->client_cert = config->client_cert;
	params->private_key = config->private_key;
	params->private_key_passwd = config->private_key_passwd;
	params->dh_file = config->dh_file;
	params->subject_match = config->subject_match;
	params->altsubject_match = config->altsubject_match;
	params->check_cert_subject = config->check_cert_subject;
	params->suffix_match = config->domain_suffix_match;
	params->domain_match = config->domain_match;
	params->engine = config->engine;
	params->engine_id = config->engine_id;
	params->pin = config->pin;
	params->key_id = config->key_id;
	params->cert_id = config->cert_id;
	params->ca_cert_id = config->ca_cert_id;
	eap_tls_params_flags(params, config->phase1);
}
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
struct eap_peer_config {int /*<<< orphan*/  phase2; int /*<<< orphan*/  ca_cert2_id; int /*<<< orphan*/  cert2_id; int /*<<< orphan*/  key2_id; int /*<<< orphan*/  pin2; int /*<<< orphan*/  engine2_id; int /*<<< orphan*/  engine2; int /*<<< orphan*/  domain_match2; int /*<<< orphan*/  domain_suffix_match2; int /*<<< orphan*/  check_cert_subject2; int /*<<< orphan*/  altsubject_match2; int /*<<< orphan*/  subject_match2; int /*<<< orphan*/  dh_file2; int /*<<< orphan*/  private_key2_passwd; int /*<<< orphan*/  private_key2; int /*<<< orphan*/  client_cert2; int /*<<< orphan*/  ca_path2; int /*<<< orphan*/  ca_cert2; } ;

/* Variables and functions */
 int /*<<< orphan*/  eap_tls_params_flags (struct tls_connection_params*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eap_tls_params_from_conf2(struct tls_connection_params *params,
				      struct eap_peer_config *config)
{
	params->ca_cert = config->ca_cert2;
	params->ca_path = config->ca_path2;
	params->client_cert = config->client_cert2;
	params->private_key = config->private_key2;
	params->private_key_passwd = config->private_key2_passwd;
	params->dh_file = config->dh_file2;
	params->subject_match = config->subject_match2;
	params->altsubject_match = config->altsubject_match2;
	params->check_cert_subject = config->check_cert_subject2;
	params->suffix_match = config->domain_suffix_match2;
	params->domain_match = config->domain_match2;
	params->engine = config->engine2;
	params->engine_id = config->engine2_id;
	params->pin = config->pin2;
	params->key_id = config->key2_id;
	params->cert_id = config->cert2_id;
	params->ca_cert_id = config->ca_cert2_id;
	eap_tls_params_flags(params, config->phase2);
}
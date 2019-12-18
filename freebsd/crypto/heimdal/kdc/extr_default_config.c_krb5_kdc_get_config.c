#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* require_preauth; void* encode_as_rep_as_tgs_rep; void* tgt_use_strongest_session_key; void* preauth_use_strongest_session_key; void* svc_use_strongest_session_key; void* use_strongest_server_key; void* check_ticket_addresses; void* allow_null_ticket_addresses; void* allow_anonymous; void* enable_pkinit; void* pkinit_princ_in_cert; void* pkinit_require_binding; int digests_allowed; void* pkinit_dh_min_bits; void* pkinit_kdc_friendly_name; void* pkinit_kdc_ocsp_file; void* pkinit_kdc_revoke; void* pkinit_kdc_cert_pool; void* pkinit_kdc_anchors; void* pkinit_kdc_identity; scalar_t__ kdc_warn_pwexpire; void* trpolicy; void* max_datagram_reply_length; void* enable_kx509; int /*<<< orphan*/ * kx509_template; int /*<<< orphan*/ * kx509_ca; void* enable_digest; int /*<<< orphan*/ * logf; scalar_t__ num_db; int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ krb5_kdc_configuration ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 void* FALSE ; 
 void* TRPOLICY_ALLOW_PER_PRINCIPAL ; 
 void* TRPOLICY_ALWAYS_CHECK ; 
 void* TRPOLICY_ALWAYS_HONOUR_REQUEST ; 
 void* TRUE ; 
 int /*<<< orphan*/  _kdc_digestunits ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  kdc_log (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 void* krb5_config_get_bool_default (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,char*,char*,int /*<<< orphan*/ *) ; 
 void* krb5_config_get_int_default (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,char*,int /*<<< orphan*/ *) ; 
 void* krb5_config_get_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 char* krb5_config_get_string_default (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ *) ; 
 void* krb5_config_get_strings (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_config_get_time_default (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int parse_flags (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

krb5_error_code
krb5_kdc_get_config(krb5_context context, krb5_kdc_configuration **config)
{
    krb5_kdc_configuration *c;

    c = calloc(1, sizeof(*c));
    if (c == NULL) {
	krb5_set_error_message(context, ENOMEM, "malloc: out of memory");
	return ENOMEM;
    }

    c->require_preauth = TRUE;
    c->kdc_warn_pwexpire = 0;
    c->encode_as_rep_as_tgs_rep = FALSE;
    c->tgt_use_strongest_session_key = FALSE;
    c->preauth_use_strongest_session_key = FALSE;
    c->svc_use_strongest_session_key = FALSE;
    c->use_strongest_server_key = TRUE;
    c->check_ticket_addresses = TRUE;
    c->allow_null_ticket_addresses = TRUE;
    c->allow_anonymous = FALSE;
    c->trpolicy = TRPOLICY_ALWAYS_CHECK;
    c->enable_pkinit = FALSE;
    c->pkinit_princ_in_cert = TRUE;
    c->pkinit_require_binding = TRUE;
    c->db = NULL;
    c->num_db = 0;
    c->logf = NULL;

    c->require_preauth =
	krb5_config_get_bool_default(context, NULL,
				     c->require_preauth,
				     "kdc", "require-preauth", NULL);
#ifdef DIGEST
    c->enable_digest =
	krb5_config_get_bool_default(context, NULL,
				     FALSE,
				     "kdc", "enable-digest", NULL);

    {
	const char *digests;

	digests = krb5_config_get_string(context, NULL,
					 "kdc",
					 "digests_allowed", NULL);
	if (digests == NULL)
	    digests = "ntlm-v2";
	c->digests_allowed = parse_flags(digests,_kdc_digestunits, 0);
	if (c->digests_allowed == -1) {
	    kdc_log(context, c, 0,
		    "unparsable digest units (%s), turning off digest",
		    digests);
	    c->enable_digest = 0;
	} else if (c->digests_allowed == 0) {
	    kdc_log(context, c, 0,
		    "no digest enable, turning digest off",
		    digests);
	    c->enable_digest = 0;
	}
    }
#endif

#ifdef KX509
    c->enable_kx509 =
	krb5_config_get_bool_default(context, NULL,
				     FALSE,
				     "kdc", "enable-kx509", NULL);

    if (c->enable_kx509) {
	c->kx509_template =
	    krb5_config_get_string(context, NULL,
				   "kdc", "kx509_template", NULL);
	c->kx509_ca =
	    krb5_config_get_string(context, NULL,
				   "kdc", "kx509_ca", NULL);
	if (c->kx509_ca == NULL || c->kx509_template == NULL) {
	    kdc_log(context, c, 0,
		    "missing kx509 configuration, turning off");
	    c->enable_kx509 = FALSE;
	}
    }
#endif

    c->tgt_use_strongest_session_key =
	krb5_config_get_bool_default(context, NULL,
				     c->tgt_use_strongest_session_key,
				     "kdc",
				     "tgt-use-strongest-session-key", NULL);
    c->preauth_use_strongest_session_key =
	krb5_config_get_bool_default(context, NULL,
				     c->preauth_use_strongest_session_key,
				     "kdc",
				     "preauth-use-strongest-session-key", NULL);
    c->svc_use_strongest_session_key =
	krb5_config_get_bool_default(context, NULL,
				     c->svc_use_strongest_session_key,
				     "kdc",
				     "svc-use-strongest-session-key", NULL);
    c->use_strongest_server_key =
	krb5_config_get_bool_default(context, NULL,
				     c->use_strongest_server_key,
				     "kdc",
				     "use-strongest-server-key", NULL);

    c->check_ticket_addresses =
	krb5_config_get_bool_default(context, NULL,
				     c->check_ticket_addresses,
				     "kdc",
				     "check-ticket-addresses", NULL);
    c->allow_null_ticket_addresses =
	krb5_config_get_bool_default(context, NULL,
				     c->allow_null_ticket_addresses,
				     "kdc",
				     "allow-null-ticket-addresses", NULL);

    c->allow_anonymous =
	krb5_config_get_bool_default(context, NULL,
				     c->allow_anonymous,
				     "kdc",
				     "allow-anonymous", NULL);

    c->max_datagram_reply_length =
	krb5_config_get_int_default(context,
				    NULL,
				    1400,
				    "kdc",
				    "max-kdc-datagram-reply-length",
				    NULL);

    {
	const char *trpolicy_str;

	trpolicy_str =
	    krb5_config_get_string_default(context, NULL, "DEFAULT", "kdc",
					   "transited-policy", NULL);
	if(strcasecmp(trpolicy_str, "always-check") == 0) {
	    c->trpolicy = TRPOLICY_ALWAYS_CHECK;
	} else if(strcasecmp(trpolicy_str, "allow-per-principal") == 0) {
	    c->trpolicy = TRPOLICY_ALLOW_PER_PRINCIPAL;
	} else if(strcasecmp(trpolicy_str, "always-honour-request") == 0) {
	    c->trpolicy = TRPOLICY_ALWAYS_HONOUR_REQUEST;
	} else if(strcasecmp(trpolicy_str, "DEFAULT") == 0) {
	    /* default */
	} else {
	    kdc_log(context, c, 0,
		    "unknown transited-policy: %s, "
		    "reverting to default (always-check)",
		    trpolicy_str);
	}
    }

    c->encode_as_rep_as_tgs_rep =
	krb5_config_get_bool_default(context, NULL,
				     c->encode_as_rep_as_tgs_rep,
				     "kdc",
				     "encode_as_rep_as_tgs_rep", NULL);

    c->kdc_warn_pwexpire =
	krb5_config_get_time_default (context, NULL,
				      c->kdc_warn_pwexpire,
				      "kdc", "kdc_warn_pwexpire", NULL);


    c->enable_pkinit =
	krb5_config_get_bool_default(context,
				     NULL,
				     c->enable_pkinit,
				     "kdc",
				     "enable-pkinit",
				     NULL);


    c->pkinit_kdc_identity =
	krb5_config_get_string(context, NULL,
			       "kdc", "pkinit_identity", NULL);
    c->pkinit_kdc_anchors =
	krb5_config_get_string(context, NULL,
			       "kdc", "pkinit_anchors", NULL);
    c->pkinit_kdc_cert_pool =
	krb5_config_get_strings(context, NULL,
				"kdc", "pkinit_pool", NULL);
    c->pkinit_kdc_revoke =
	krb5_config_get_strings(context, NULL,
				"kdc", "pkinit_revoke", NULL);
    c->pkinit_kdc_ocsp_file =
	krb5_config_get_string(context, NULL,
			       "kdc", "pkinit_kdc_ocsp", NULL);
    c->pkinit_kdc_friendly_name =
	krb5_config_get_string(context, NULL,
			       "kdc", "pkinit_kdc_friendly_name", NULL);
    c->pkinit_princ_in_cert =
	krb5_config_get_bool_default(context, NULL,
				     c->pkinit_princ_in_cert,
				     "kdc",
				     "pkinit_principal_in_certificate",
				     NULL);
    c->pkinit_require_binding =
	krb5_config_get_bool_default(context, NULL,
				     c->pkinit_require_binding,
				     "kdc",
				     "pkinit_win2k_require_binding",
				     NULL);
    c->pkinit_dh_min_bits =
	krb5_config_get_int_default(context, NULL,
				    0,
				    "kdc", "pkinit_dh_min_bits", NULL);

    *config = c;

    return 0;
}
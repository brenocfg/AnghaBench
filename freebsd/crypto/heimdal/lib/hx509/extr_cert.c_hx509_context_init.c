#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hx509_context ;
struct TYPE_12__ {int /*<<< orphan*/  default_trust_anchors; int /*<<< orphan*/  et_list; int /*<<< orphan*/  ocsp_time_diff; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_add_conf_module () ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HX509_DEFAULT_ANCHORS ; 
 int /*<<< orphan*/  HX509_DEFAULT_OCSP_TIME_DIFF ; 
 int /*<<< orphan*/  OpenSSL_add_all_algorithms () ; 
 int /*<<< orphan*/  _hx509_ks_dir_register (TYPE_1__*) ; 
 int /*<<< orphan*/  _hx509_ks_file_register (TYPE_1__*) ; 
 int /*<<< orphan*/  _hx509_ks_keychain_register (TYPE_1__*) ; 
 int /*<<< orphan*/  _hx509_ks_mem_register (TYPE_1__*) ; 
 int /*<<< orphan*/  _hx509_ks_null_register (TYPE_1__*) ; 
 int /*<<< orphan*/  _hx509_ks_pkcs11_register (TYPE_1__*) ; 
 int /*<<< orphan*/  _hx509_ks_pkcs12_register (TYPE_1__*) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  hx509_certs_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initialize_asn1_error_table_r (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initialize_hx_error_table_r (int /*<<< orphan*/ *) ; 

int
hx509_context_init(hx509_context *context)
{
    *context = calloc(1, sizeof(**context));
    if (*context == NULL)
	return ENOMEM;

    _hx509_ks_null_register(*context);
    _hx509_ks_mem_register(*context);
    _hx509_ks_file_register(*context);
    _hx509_ks_pkcs12_register(*context);
    _hx509_ks_pkcs11_register(*context);
    _hx509_ks_dir_register(*context);
    _hx509_ks_keychain_register(*context);

    ENGINE_add_conf_module();
    OpenSSL_add_all_algorithms();

    (*context)->ocsp_time_diff = HX509_DEFAULT_OCSP_TIME_DIFF;

    initialize_hx_error_table_r(&(*context)->et_list);
    initialize_asn1_error_table_r(&(*context)->et_list);

#ifdef HX509_DEFAULT_ANCHORS
    (void)hx509_certs_init(*context, HX509_DEFAULT_ANCHORS, 0,
			   NULL, &(*context)->default_trust_anchors);
#endif

    return 0;
}
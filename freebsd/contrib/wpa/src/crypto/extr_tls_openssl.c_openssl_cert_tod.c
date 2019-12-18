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
typedef  scalar_t__ stack_index_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_3__ {int /*<<< orphan*/  policyid; } ;
typedef  TYPE_1__ POLICYINFO ;
typedef  int /*<<< orphan*/  CERTIFICATEPOLICIES ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  NID_certificate_policies ; 
 int OBJ_obj2txt (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * X509_get_ext_d2i (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 scalar_t__ sk_POLICYINFO_num (int /*<<< orphan*/ *) ; 
 TYPE_1__* sk_POLICYINFO_value (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int openssl_cert_tod(X509 *cert)
{
	CERTIFICATEPOLICIES *ext;
	stack_index_t i;
	char buf[100];
	int res;
	int tod = 0;

	ext = X509_get_ext_d2i(cert, NID_certificate_policies, NULL, NULL);
	if (!ext)
		return 0;

	for (i = 0; i < sk_POLICYINFO_num(ext); i++) {
		POLICYINFO *policy;

		policy = sk_POLICYINFO_value(ext, i);
		res = OBJ_obj2txt(buf, sizeof(buf), policy->policyid, 0);
		if (res < 0 || (size_t) res >= sizeof(buf))
			continue;
		wpa_printf(MSG_DEBUG, "OpenSSL: Certificate Policy %s", buf);
		if (os_strcmp(buf, "1.3.6.1.4.1.40808.1.3.1") == 0)
			tod = 1;
	}

	return tod;
}
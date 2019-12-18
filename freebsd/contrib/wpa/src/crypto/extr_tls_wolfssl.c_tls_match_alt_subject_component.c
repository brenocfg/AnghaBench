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
typedef  int /*<<< orphan*/  WOLFSSL_X509 ;
struct TYPE_3__ {int type; scalar_t__ obj; } ;
typedef  TYPE_1__ WOLFSSL_ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ALT_NAMES_OID ; 
 scalar_t__ os_memcmp (char const*,scalar_t__,size_t) ; 
 size_t os_strlen (char*) ; 
 void* wolfSSL_X509_get_ext_d2i (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wolfSSL_sk_ASN1_OBJECT_free (void*) ; 
 int wolfSSL_sk_num (void*) ; 
 TYPE_1__* wolfSSL_sk_value (void*,int) ; 

__attribute__((used)) static int tls_match_alt_subject_component(WOLFSSL_X509 *cert, int type,
					   const char *value, size_t len)
{
	WOLFSSL_ASN1_OBJECT *gen;
	void *ext;
	int found = 0;
	int i;

	ext = wolfSSL_X509_get_ext_d2i(cert, ALT_NAMES_OID, NULL, NULL);

	for (i = 0; ext && i < wolfSSL_sk_num(ext); i++) {
		gen = wolfSSL_sk_value(ext, i);
		if (gen->type != type)
			continue;
		if (os_strlen((char *) gen->obj) == len &&
		    os_memcmp(value, gen->obj, len) == 0)
			found++;
	}

	wolfSSL_sk_ASN1_OBJECT_free(ext);

	return found;
}
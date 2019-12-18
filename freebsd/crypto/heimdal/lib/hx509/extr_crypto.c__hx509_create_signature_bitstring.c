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
typedef  int /*<<< orphan*/  hx509_private_key ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_7__ {int length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ heim_octet_string ;
struct TYPE_8__ {int length; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ heim_bit_string ;
typedef  int /*<<< orphan*/  AlgorithmIdentifier ;

/* Variables and functions */
 int _hx509_create_signature (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const*,TYPE_1__ const*,int /*<<< orphan*/ *,TYPE_1__*) ; 

int
_hx509_create_signature_bitstring(hx509_context context,
				  const hx509_private_key signer,
				  const AlgorithmIdentifier *alg,
				  const heim_octet_string *data,
				  AlgorithmIdentifier *signatureAlgorithm,
				  heim_bit_string *sig)
{
    heim_octet_string os;
    int ret;

    ret = _hx509_create_signature(context, signer, alg,
				  data, signatureAlgorithm, &os);
    if (ret)
	return ret;
    sig->data = os.data;
    sig->length = os.length * 8;
    return 0;
}
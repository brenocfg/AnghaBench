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
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_cert ;
struct TYPE_7__ {int length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ heim_octet_string ;
struct TYPE_8__ {int length; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ heim_bit_string ;
typedef  int /*<<< orphan*/  AlgorithmIdentifier ;

/* Variables and functions */
 int HX509_CRYPTO_SIG_INVALID_FORMAT ; 
 int _hx509_verify_signature (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const*,TYPE_1__ const*,TYPE_1__*) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

int
_hx509_verify_signature_bitstring(hx509_context context,
				  const hx509_cert signer,
				  const AlgorithmIdentifier *alg,
				  const heim_octet_string *data,
				  const heim_bit_string *sig)
{
    heim_octet_string os;

    if (sig->length & 7) {
	hx509_set_error_string(context, 0, HX509_CRYPTO_SIG_INVALID_FORMAT,
			       "signature not multiple of 8 bits");
	return HX509_CRYPTO_SIG_INVALID_FORMAT;
    }

    os.data = sig->data;
    os.length = sig->length / 8;

    return _hx509_verify_signature(context, signer, alg, data, &os);
}
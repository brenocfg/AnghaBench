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
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_cert ;
typedef  int /*<<< orphan*/  heim_octet_string ;
typedef  int /*<<< orphan*/  AlgorithmIdentifier ;

/* Variables and functions */
 int _hx509_verify_signature (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

int
hx509_verify_signature(hx509_context context,
		       const hx509_cert signer,
		       const AlgorithmIdentifier *alg,
		       const heim_octet_string *data,
		       const heim_octet_string *sig)
{
    return _hx509_verify_signature(context, signer, alg, data, sig);
}
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
struct revoke_ocsp {int /*<<< orphan*/  signer; int /*<<< orphan*/  certs; int /*<<< orphan*/  ocsp; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_OCSPBasicOCSPResponse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_cert_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_certs_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_ocsp(struct revoke_ocsp *ocsp)
{
    free(ocsp->path);
    free_OCSPBasicOCSPResponse(&ocsp->ocsp);
    hx509_certs_free(&ocsp->certs);
    hx509_cert_free(ocsp->signer);
}
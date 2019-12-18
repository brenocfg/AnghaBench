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
struct TYPE_3__ {int len; unsigned char const* p; int /*<<< orphan*/  tag; } ;
typedef  TYPE_1__ x509_buf ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_BIT_STRING ; 
 int /*<<< orphan*/  SVN_ERR_X509_CERT_INVALID_SIGNATURE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * asn1_get_tag (unsigned char const**,unsigned char const*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
x509_get_sig(const unsigned char **p, const unsigned char *end, x509_buf * sig)
{
  svn_error_t *err;
  ptrdiff_t len;

  err = asn1_get_tag(p, end, &len, ASN1_BIT_STRING);
  if (err)
    return svn_error_create(SVN_ERR_X509_CERT_INVALID_SIGNATURE, err, NULL);

  sig->tag = ASN1_BIT_STRING;

  if (--len < 1 || *(*p)++ != 0)
    return svn_error_create(SVN_ERR_X509_CERT_INVALID_SIGNATURE, NULL, NULL);

  sig->len = len;
  sig->p = *p;

  *p += len;

  return SVN_NO_ERROR;
}
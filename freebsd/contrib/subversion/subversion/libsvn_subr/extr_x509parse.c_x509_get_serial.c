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
struct TYPE_3__ {unsigned char const* p; int /*<<< orphan*/  len; int /*<<< orphan*/  tag; } ;
typedef  TYPE_1__ x509_buf ;
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int ASN1_CONTEXT_SPECIFIC ; 
 unsigned char const ASN1_INTEGER ; 
 int ASN1_PRIMITIVE ; 
 int /*<<< orphan*/  SVN_ERR_ASN1_OUT_OF_DATA ; 
 int /*<<< orphan*/  SVN_ERR_ASN1_UNEXPECTED_TAG ; 
 int /*<<< orphan*/  SVN_ERR_X509_CERT_INVALID_SERIAL ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * asn1_get_len (unsigned char const**,unsigned char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
x509_get_serial(const unsigned char **p,
                const unsigned char *end, x509_buf * serial)
{
  svn_error_t *err;

  if ((end - *p) < 1)
    {
      err = svn_error_create(SVN_ERR_ASN1_OUT_OF_DATA, NULL, NULL);
      return svn_error_create(SVN_ERR_X509_CERT_INVALID_SERIAL, err, NULL);
    }

  if (**p != (ASN1_CONTEXT_SPECIFIC | ASN1_PRIMITIVE | 2) &&
      **p != ASN1_INTEGER)
    {
      err = svn_error_create(SVN_ERR_ASN1_UNEXPECTED_TAG, NULL, NULL);
      return svn_error_create(SVN_ERR_X509_CERT_INVALID_SERIAL, err, NULL);
    }

  serial->tag = *(*p)++;

  err = asn1_get_len(p, end, &serial->len);
  if (err)
    return svn_error_create(SVN_ERR_X509_CERT_INVALID_SERIAL, err, NULL);

  serial->p = *p;
  *p += serial->len;

  return SVN_NO_ERROR;
}
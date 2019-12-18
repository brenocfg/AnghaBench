#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int tag; unsigned char const* p; int /*<<< orphan*/  len; } ;
struct TYPE_4__ {int /*<<< orphan*/ * next; TYPE_2__ val; TYPE_2__ oid; } ;
typedef  TYPE_1__ x509_name ;
typedef  TYPE_2__ x509_buf ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 unsigned char const ASN1_BMP_STRING ; 
 int ASN1_CONSTRUCTED ; 
 unsigned char const ASN1_IA5_STRING ; 
 int ASN1_OID ; 
 unsigned char const ASN1_PRINTABLE_STRING ; 
 int ASN1_SEQUENCE ; 
 unsigned char const ASN1_T61_STRING ; 
 unsigned char const ASN1_UNIVERSAL_STRING ; 
 unsigned char const ASN1_UTF8_STRING ; 
 int /*<<< orphan*/  SVN_ERR_ASN1_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  SVN_ERR_ASN1_OUT_OF_DATA ; 
 int /*<<< orphan*/  SVN_ERR_ASN1_UNEXPECTED_TAG ; 
 int /*<<< orphan*/  SVN_ERR_X509_CERT_INVALID_NAME ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * asn1_get_len (unsigned char const**,unsigned char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * asn1_get_tag (unsigned char const**,unsigned char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
x509_get_attribute(const unsigned char **p, const unsigned char *end,
                   x509_name *cur, apr_pool_t *result_pool)
{
  svn_error_t *err;
  ptrdiff_t len;
  x509_buf *oid;
  x509_buf *val;

  err = asn1_get_tag(p, end, &len, ASN1_CONSTRUCTED | ASN1_SEQUENCE);
  if (err)
    return svn_error_create(SVN_ERR_X509_CERT_INVALID_NAME, err, NULL);

  end = *p + len;

  oid = &cur->oid;

  err = asn1_get_tag(p, end, &oid->len, ASN1_OID);
  if (err)
    return svn_error_create(SVN_ERR_X509_CERT_INVALID_NAME, err, NULL);

  oid->tag = ASN1_OID;
  oid->p = *p;
  *p += oid->len;

  if ((end - *p) < 1)
    {
      err = svn_error_create(SVN_ERR_ASN1_OUT_OF_DATA, NULL, NULL);
      return svn_error_create(SVN_ERR_X509_CERT_INVALID_NAME, err, NULL);
    }

  if (**p != ASN1_BMP_STRING && **p != ASN1_UTF8_STRING &&
      **p != ASN1_T61_STRING && **p != ASN1_PRINTABLE_STRING &&
      **p != ASN1_IA5_STRING && **p != ASN1_UNIVERSAL_STRING)
    {
      err = svn_error_create(SVN_ERR_ASN1_UNEXPECTED_TAG, NULL, NULL);
      return svn_error_create(SVN_ERR_X509_CERT_INVALID_NAME, err, NULL);
    }

  val = &cur->val;
  val->tag = *(*p)++;

  err = asn1_get_len(p, end, &val->len);
  if (err)
    return svn_error_create(SVN_ERR_X509_CERT_INVALID_NAME, err, NULL);

  val->p = *p;
  *p += val->len;

  cur->next = NULL;

  if (*p != end)
    {
      err = svn_error_create(SVN_ERR_ASN1_LENGTH_MISMATCH, NULL, NULL);
      return svn_error_create(SVN_ERR_X509_CERT_INVALID_NAME, err, NULL);
    }

  return SVN_NO_ERROR;
}
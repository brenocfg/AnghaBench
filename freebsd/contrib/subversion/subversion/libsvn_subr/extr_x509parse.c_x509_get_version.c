#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int ASN1_CONSTRUCTED ; 
 int ASN1_CONTEXT_SPECIFIC ; 
 int /*<<< orphan*/  SVN_ERR_ASN1_LENGTH_MISMATCH ; 
 scalar_t__ SVN_ERR_ASN1_UNEXPECTED_TAG ; 
 int /*<<< orphan*/  SVN_ERR_X509_CERT_INVALID_VERSION ; 
 TYPE_1__* SVN_NO_ERROR ; 
 TYPE_1__* asn1_get_int (unsigned char const**,unsigned char const*,int*) ; 
 TYPE_1__* asn1_get_tag (unsigned char const**,unsigned char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_create (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 

__attribute__((used)) static svn_error_t *
x509_get_version(const unsigned char **p, const unsigned char *end, int *ver)
{
  svn_error_t *err;
  ptrdiff_t len;

  /*
   * As defined in the Basic Certificate fields:
   *   version         [0]  EXPLICIT Version DEFAULT v1,
   * the version is the context specific tag 0.
   */
  err = asn1_get_tag(p, end, &len,
                     ASN1_CONTEXT_SPECIFIC | ASN1_CONSTRUCTED | 0);
  if (err)
    {
      if (err->apr_err == SVN_ERR_ASN1_UNEXPECTED_TAG)
        {
          svn_error_clear(err);
          *ver = 0;
          return SVN_NO_ERROR;
        }

      return svn_error_trace(err);
    }

  end = *p + len;

  err = asn1_get_int(p, end, ver);
  if (err)
    return svn_error_create(SVN_ERR_X509_CERT_INVALID_VERSION, err, NULL);

  if (*p != end)
    {
      err = svn_error_create(SVN_ERR_ASN1_LENGTH_MISMATCH, NULL, NULL);
      return svn_error_create(SVN_ERR_X509_CERT_INVALID_VERSION, err, NULL);
    }

  return SVN_NO_ERROR;
}
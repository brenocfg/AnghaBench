#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int version; int /*<<< orphan*/  valid_to; int /*<<< orphan*/  valid_from; int /*<<< orphan*/  issuer; int /*<<< orphan*/  subject; int /*<<< orphan*/  sig; int /*<<< orphan*/  sig_oid2; int /*<<< orphan*/  sig_oid1; int /*<<< orphan*/  dnsnames; int /*<<< orphan*/  subject_id; int /*<<< orphan*/  issuer_id; int /*<<< orphan*/  serial; } ;
typedef  TYPE_1__ x509_cert ;
typedef  int /*<<< orphan*/  x509_buf ;
struct TYPE_7__ {int /*<<< orphan*/  digest; int /*<<< orphan*/  valid_to; int /*<<< orphan*/  valid_from; int /*<<< orphan*/  issuer; int /*<<< orphan*/  subject; } ;
typedef  TYPE_2__ svn_x509_certinfo_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int ptrdiff_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int ASN1_CONSTRUCTED ; 
 int ASN1_SEQUENCE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASN1_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  SVN_ERR_X509_CERT_INVALID_FORMAT ; 
 int /*<<< orphan*/  SVN_ERR_X509_CERT_SIG_MISMATCH ; 
 int /*<<< orphan*/  SVN_ERR_X509_CERT_UNKNOWN_VERSION ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * asn1_get_tag (unsigned char const**,unsigned char const*,int*,int) ; 
 int /*<<< orphan*/  oids_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_sha1 ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x509_get_alg (unsigned char const**,unsigned char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x509_get_dates (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char const**,unsigned char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x509_get_ext (int /*<<< orphan*/ ,unsigned char const**,unsigned char const*) ; 
 int /*<<< orphan*/  x509_get_name (unsigned char const**,unsigned char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x509_get_serial (unsigned char const**,unsigned char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x509_get_sig (unsigned char const**,unsigned char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x509_get_uid (unsigned char const**,unsigned char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  x509_get_version (unsigned char const**,unsigned char const*,int*) ; 
 int /*<<< orphan*/  x509_name_to_certinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x509parse_get_hostnames (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_x509_parse_cert(svn_x509_certinfo_t **certinfo,
                    const char *buf,
                    apr_size_t buflen,
                    apr_pool_t *result_pool,
                    apr_pool_t *scratch_pool)
{
  svn_error_t *err;
  ptrdiff_t len;
  const unsigned char *p;
  const unsigned char *end;
  x509_cert *crt;
  svn_x509_certinfo_t *ci;

  crt = apr_pcalloc(scratch_pool, sizeof(*crt));
  p = (const unsigned char *)buf;
  len = buflen;
  end = p + len;

  /*
   * Certificate  ::=      SEQUENCE  {
   *              tbsCertificate           TBSCertificate,
   *              signatureAlgorithm       AlgorithmIdentifier,
   *              signatureValue           BIT STRING      }
   */
  err = asn1_get_tag(&p, end, &len, ASN1_CONSTRUCTED | ASN1_SEQUENCE);
  if (err)
    return svn_error_create(SVN_ERR_X509_CERT_INVALID_FORMAT, err, NULL);

  if (len != (end - p))
    {
      err = svn_error_create(SVN_ERR_ASN1_LENGTH_MISMATCH, NULL, NULL);
      return svn_error_create(SVN_ERR_X509_CERT_INVALID_FORMAT, err, NULL);
    }

  /*
   * TBSCertificate  ::=  SEQUENCE  {
   */
  err = asn1_get_tag(&p, end, &len, ASN1_CONSTRUCTED | ASN1_SEQUENCE);
  if (err)
    return svn_error_create(SVN_ERR_X509_CERT_INVALID_FORMAT, err, NULL);

  end = p + len;

  /*
   * Version      ::=      INTEGER  {      v1(0), v2(1), v3(2)  }
   *
   * CertificateSerialNumber      ::=      INTEGER
   *
   * signature                    AlgorithmIdentifier
   */
  SVN_ERR(x509_get_version(&p, end, &crt->version));
  SVN_ERR(x509_get_serial(&p, end, &crt->serial));
  SVN_ERR(x509_get_alg(&p, end, &crt->sig_oid1));

  crt->version++;

  if (crt->version > 3)
    return svn_error_create(SVN_ERR_X509_CERT_UNKNOWN_VERSION, NULL, NULL);

  /*
   * issuer                               Name
   */
  err = asn1_get_tag(&p, end, &len, ASN1_CONSTRUCTED | ASN1_SEQUENCE);
  if (err)
    return svn_error_create(SVN_ERR_X509_CERT_INVALID_FORMAT, err, NULL);

  SVN_ERR(x509_get_name(&p, p + len, &crt->issuer, scratch_pool));

  /*
   * Validity ::= SEQUENCE {
   *              notBefore          Time,
   *              notAfter           Time }
   *
   */
  SVN_ERR(x509_get_dates(&crt->valid_from, &crt->valid_to, &p, end,
                         scratch_pool));

  /*
   * subject                              Name
   */
  err = asn1_get_tag(&p, end, &len, ASN1_CONSTRUCTED | ASN1_SEQUENCE);
  if (err)
    return svn_error_create(SVN_ERR_X509_CERT_INVALID_FORMAT, err, NULL);

  SVN_ERR(x509_get_name(&p, p + len, &crt->subject, scratch_pool));

  /*
   * SubjectPublicKeyInfo  ::=  SEQUENCE
   *              algorithm                        AlgorithmIdentifier,
   *              subjectPublicKey         BIT STRING      }
   */
  err = asn1_get_tag(&p, end, &len, ASN1_CONSTRUCTED | ASN1_SEQUENCE);
  if (err)
    return svn_error_create(SVN_ERR_X509_CERT_INVALID_FORMAT, err, NULL);

  /* Skip pubkey. */
  p += len;

  /*
   *      issuerUniqueID  [1]      IMPLICIT UniqueIdentifier OPTIONAL,
   *                                               -- If present, version shall be v2 or v3
   *      subjectUniqueID [2]      IMPLICIT UniqueIdentifier OPTIONAL,
   *                                               -- If present, version shall be v2 or v3
   *      extensions              [3]      EXPLICIT Extensions OPTIONAL
   *                                               -- If present, version shall be v3
   */
  crt->dnsnames = apr_array_make(scratch_pool, 3, sizeof(x509_buf *));

  /* Try to parse issuerUniqueID, subjectUniqueID and extensions for *every*
   * version (X.509 v1, v2 and v3), not just v2 or v3.  If they aren't present,
   * we are fine, but we don't want to throw an error if they are.  v1 and v2
   * certificates with the corresponding extra fields are ill-formed per RFC
   * 5280 s. 4.1, but we suspect they could exist in the real world.  Other
   * X.509 parsers (e.g., within OpenSSL or Microsoft CryptoAPI) aren't picky
   * about these certificates, and we also allow them. */
  SVN_ERR(x509_get_uid(&p, end, &crt->issuer_id, 1));
  SVN_ERR(x509_get_uid(&p, end, &crt->subject_id, 2));
  SVN_ERR(x509_get_ext(crt->dnsnames, &p, end));

  if (p != end)
    {
      err = svn_error_create(SVN_ERR_ASN1_LENGTH_MISMATCH, NULL, NULL);
      return svn_error_create(SVN_ERR_X509_CERT_INVALID_FORMAT, err, NULL);
    }

  end = (const unsigned char*) buf + buflen;

  /*
   *      signatureAlgorithm       AlgorithmIdentifier,
   *      signatureValue           BIT STRING
   */
  SVN_ERR(x509_get_alg(&p, end, &crt->sig_oid2));

  if (!oids_equal(&crt->sig_oid1, &crt->sig_oid2))
    return svn_error_create(SVN_ERR_X509_CERT_SIG_MISMATCH, NULL, NULL);

  SVN_ERR(x509_get_sig(&p, end, &crt->sig));

  if (p != end)
    {
      err = svn_error_create(SVN_ERR_ASN1_LENGTH_MISMATCH, NULL, NULL);
      return svn_error_create(SVN_ERR_X509_CERT_INVALID_FORMAT, err, NULL);
    }

  ci = apr_pcalloc(result_pool, sizeof(*ci));

  /* Get the subject name */
  SVN_ERR(x509_name_to_certinfo(&ci->subject, &crt->subject,
                                scratch_pool, result_pool));

  /* Get the issuer name */
  SVN_ERR(x509_name_to_certinfo(&ci->issuer, &crt->issuer,
                                scratch_pool, result_pool));

  /* Copy the validity range */
  ci->valid_from = crt->valid_from;
  ci->valid_to = crt->valid_to;

  /* Calculate the SHA1 digest of the certificate, otherwise known as
    the fingerprint */
  SVN_ERR(svn_checksum(&ci->digest, svn_checksum_sha1, buf, buflen,
                       result_pool));

  /* Construct the array of host names */
  x509parse_get_hostnames(ci, crt, result_pool, scratch_pool);

  *certinfo = ci;
  return SVN_NO_ERROR;
}
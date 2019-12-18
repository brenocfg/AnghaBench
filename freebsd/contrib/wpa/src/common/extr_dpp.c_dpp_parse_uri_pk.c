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
typedef  unsigned char const u8 ;
struct dpp_bootstrap_info {unsigned char const* pubkey_hash; int /*<<< orphan*/ * pubkey; int /*<<< orphan*/  curve; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  X509_PUBKEY ;
typedef  int /*<<< orphan*/  X509_ALGOR ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  const ASN1_OBJECT ;

/* Variables and functions */
 scalar_t__ EVP_PKEY_EC ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_id (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int OBJ_obj2txt (char*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int SHA256_MAC_LEN ; 
 int V_ASN1_OBJECT ; 
 int /*<<< orphan*/  X509_ALGOR_get0 (int /*<<< orphan*/  const**,int*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_PUBKEY_free (int /*<<< orphan*/ *) ; 
 int X509_PUBKEY_get0_param (int /*<<< orphan*/  const**,unsigned char const**,int*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int X509_PUBKEY_set (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 unsigned char* base64_decode (unsigned char const*,int,size_t*) ; 
 int /*<<< orphan*/ * d2i_PUBKEY (int /*<<< orphan*/ *,unsigned char const**,size_t) ; 
 int /*<<< orphan*/  dpp_get_curve_oid (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  os_free (unsigned char const*) ; 
 char* os_strchr (char const*,char) ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 scalar_t__ sha256_vector (int,unsigned char const**,size_t*,unsigned char const*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int dpp_parse_uri_pk(struct dpp_bootstrap_info *bi, const char *info)
{
	const char *end;
	u8 *data;
	size_t data_len;
	EVP_PKEY *pkey;
	const unsigned char *p;
	int res;
	X509_PUBKEY *pub = NULL;
	ASN1_OBJECT *ppkalg;
	const unsigned char *pk;
	int ppklen;
	X509_ALGOR *pa;
#if OPENSSL_VERSION_NUMBER < 0x10100000L || \
	(defined(LIBRESSL_VERSION_NUMBER) && \
	 LIBRESSL_VERSION_NUMBER < 0x20800000L)
	ASN1_OBJECT *pa_oid;
#else
	const ASN1_OBJECT *pa_oid;
#endif
	const void *pval;
	int ptype;
	const ASN1_OBJECT *poid;
	char buf[100];

	end = os_strchr(info, ';');
	if (!end)
		return -1;

	data = base64_decode((const unsigned char *) info, end - info,
			     &data_len);
	if (!data) {
		wpa_printf(MSG_DEBUG,
			   "DPP: Invalid base64 encoding on URI public-key");
		return -1;
	}
	wpa_hexdump(MSG_DEBUG, "DPP: Base64 decoded URI public-key",
		    data, data_len);

	if (sha256_vector(1, (const u8 **) &data, &data_len,
			  bi->pubkey_hash) < 0) {
		wpa_printf(MSG_DEBUG, "DPP: Failed to hash public key");
		os_free(data);
		return -1;
	}
	wpa_hexdump(MSG_DEBUG, "DPP: Public key hash",
		    bi->pubkey_hash, SHA256_MAC_LEN);

	/* DER encoded ASN.1 SubjectPublicKeyInfo
	 *
	 * SubjectPublicKeyInfo  ::=  SEQUENCE  {
	 *      algorithm            AlgorithmIdentifier,
	 *      subjectPublicKey     BIT STRING  }
	 *
	 * AlgorithmIdentifier  ::=  SEQUENCE  {
	 *      algorithm               OBJECT IDENTIFIER,
	 *      parameters              ANY DEFINED BY algorithm OPTIONAL  }
	 *
	 * subjectPublicKey = compressed format public key per ANSI X9.63
	 * algorithm = ecPublicKey (1.2.840.10045.2.1)
	 * parameters = shall be present and shall be OBJECT IDENTIFIER; e.g.,
	 *       prime256v1 (1.2.840.10045.3.1.7)
	 */

	p = data;
	pkey = d2i_PUBKEY(NULL, &p, data_len);
	os_free(data);

	if (!pkey) {
		wpa_printf(MSG_DEBUG,
			   "DPP: Could not parse URI public-key SubjectPublicKeyInfo");
		return -1;
	}

	if (EVP_PKEY_type(EVP_PKEY_id(pkey)) != EVP_PKEY_EC) {
		wpa_printf(MSG_DEBUG,
			   "DPP: SubjectPublicKeyInfo does not describe an EC key");
		EVP_PKEY_free(pkey);
		return -1;
	}

	res = X509_PUBKEY_set(&pub, pkey);
	if (res != 1) {
		wpa_printf(MSG_DEBUG, "DPP: Could not set pubkey");
		goto fail;
	}

	res = X509_PUBKEY_get0_param(&ppkalg, &pk, &ppklen, &pa, pub);
	if (res != 1) {
		wpa_printf(MSG_DEBUG,
			   "DPP: Could not extract SubjectPublicKeyInfo parameters");
		goto fail;
	}
	res = OBJ_obj2txt(buf, sizeof(buf), ppkalg, 0);
	if (res < 0 || (size_t) res >= sizeof(buf)) {
		wpa_printf(MSG_DEBUG,
			   "DPP: Could not extract SubjectPublicKeyInfo algorithm");
		goto fail;
	}
	wpa_printf(MSG_DEBUG, "DPP: URI subjectPublicKey algorithm: %s", buf);
	if (os_strcmp(buf, "id-ecPublicKey") != 0) {
		wpa_printf(MSG_DEBUG,
			   "DPP: Unsupported SubjectPublicKeyInfo algorithm");
		goto fail;
	}

	X509_ALGOR_get0(&pa_oid, &ptype, (void *) &pval, pa);
	if (ptype != V_ASN1_OBJECT) {
		wpa_printf(MSG_DEBUG,
			   "DPP: SubjectPublicKeyInfo parameters did not contain an OID");
		goto fail;
	}
	poid = pval;
	res = OBJ_obj2txt(buf, sizeof(buf), poid, 0);
	if (res < 0 || (size_t) res >= sizeof(buf)) {
		wpa_printf(MSG_DEBUG,
			   "DPP: Could not extract SubjectPublicKeyInfo parameters OID");
		goto fail;
	}
	wpa_printf(MSG_DEBUG, "DPP: URI subjectPublicKey parameters: %s", buf);
	bi->curve = dpp_get_curve_oid(poid);
	if (!bi->curve) {
		wpa_printf(MSG_DEBUG,
			   "DPP: Unsupported SubjectPublicKeyInfo curve: %s",
			   buf);
		goto fail;
	}

	wpa_hexdump(MSG_DEBUG, "DPP: URI subjectPublicKey", pk, ppklen);

	X509_PUBKEY_free(pub);
	bi->pubkey = pkey;
	return 0;
fail:
	X509_PUBKEY_free(pub);
	EVP_PKEY_free(pkey);
	return -1;
}
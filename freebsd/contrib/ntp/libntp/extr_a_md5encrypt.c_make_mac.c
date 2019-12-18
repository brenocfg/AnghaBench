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
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_6__ {size_t len; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ rwbuffT ;
struct TYPE_7__ {void* buf; int len; } ;
typedef  TYPE_2__ robuffT ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  CMAC_CTX ;

/* Variables and functions */
 int AES_128_KEY_SIZE ; 
 int CMAC ; 
 int /*<<< orphan*/  CMAC_CTX_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CMAC_CTX_new () ; 
 int /*<<< orphan*/  CMAC_Final (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  CMAC_Init (int /*<<< orphan*/ *,void const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CMAC_Update (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  EVP_DigestFinal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  EVP_DigestInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  EVP_MD_CTX_FLAG_NON_FIPS_ALLOW ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  EVP_MD_CTX_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_MD_CTX_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_aes_128_cbc () ; 
 int /*<<< orphan*/  EVP_get_digestbynid (int) ; 
 int /*<<< orphan*/  INIT_SSL () ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int NID_cmac ; 
 int NID_md5 ; 
 int OBJ_nid2sn (int) ; 
 size_t cmac_ctx_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static size_t
make_mac(
	const rwbuffT *	digest,
	int		ktype,
	const robuffT *	key,
	const robuffT *	msg)
{
	/*
	 * Compute digest of key concatenated with packet. Note: the
	 * key type and digest type have been verified when the key
	 * was created.
	 */
	size_t	retlen = 0;
	
#ifdef OPENSSL
	
	INIT_SSL();

	/* Check if CMAC key type specific code required */
#   ifdef ENABLE_CMAC
	if (ktype == NID_cmac) {
		CMAC_CTX *	ctx    = NULL;
		void const *	keyptr = key->buf;
		u_char		keybuf[AES_128_KEY_SIZE];

		/* adjust key size (zero padded buffer) if necessary */
		if (AES_128_KEY_SIZE > key->len) {
			memcpy(keybuf, keyptr, key->len);
			memset((keybuf + key->len), 0,
			       (AES_128_KEY_SIZE - key->len));
			keyptr = keybuf;
		}
		
		if (NULL == (ctx = CMAC_CTX_new())) {
			msyslog(LOG_ERR, "MAC encrypt: CMAC %s CTX new failed.", CMAC);
			goto cmac_fail;
		}
		if (!CMAC_Init(ctx, keyptr, AES_128_KEY_SIZE, EVP_aes_128_cbc(), NULL)) {
			msyslog(LOG_ERR, "MAC encrypt: CMAC %s Init failed.",    CMAC);
			goto cmac_fail;
		}
		if (cmac_ctx_size(ctx) > digest->len) {
			msyslog(LOG_ERR, "MAC encrypt: CMAC %s buf too small.",  CMAC);
			goto cmac_fail;
		}
		if (!CMAC_Update(ctx, msg->buf, msg->len)) {
			msyslog(LOG_ERR, "MAC encrypt: CMAC %s Update failed.",  CMAC);
			goto cmac_fail;
		}
		if (!CMAC_Final(ctx, digest->buf, &retlen)) {
			msyslog(LOG_ERR, "MAC encrypt: CMAC %s Final failed.",   CMAC);
			retlen = 0;
		}
	  cmac_fail:
		if (ctx)
			CMAC_CTX_cleanup(ctx);
	}
	else
#   endif /*ENABLE_CMAC*/
	{	/* generic MAC handling */
		EVP_MD_CTX *	ctx   = EVP_MD_CTX_new();
		u_int		uilen = 0;
		
		if ( ! ctx) {
			msyslog(LOG_ERR, "MAC encrypt: MAC %s Digest CTX new failed.",
				OBJ_nid2sn(ktype));
			goto mac_fail;
		}
		
           #ifdef EVP_MD_CTX_FLAG_NON_FIPS_ALLOW
		/* make sure MD5 is allowd */
		EVP_MD_CTX_set_flags(ctx, EVP_MD_CTX_FLAG_NON_FIPS_ALLOW);
           #endif
		/* [Bug 3457] DON'T use plain EVP_DigestInit! It would
		 * kill the flags! */
		if (!EVP_DigestInit_ex(ctx, EVP_get_digestbynid(ktype), NULL)) {
			msyslog(LOG_ERR, "MAC encrypt: MAC %s Digest Init failed.",
				OBJ_nid2sn(ktype));
			goto mac_fail;
		}
		if ((size_t)EVP_MD_CTX_size(ctx) > digest->len) {
			msyslog(LOG_ERR, "MAC encrypt: MAC %s buf too small.",
				OBJ_nid2sn(ktype));
			goto mac_fail;
		}
		if (!EVP_DigestUpdate(ctx, key->buf, (u_int)key->len)) {
			msyslog(LOG_ERR, "MAC encrypt: MAC %s Digest Update key failed.",
				OBJ_nid2sn(ktype));
			goto mac_fail;
		}
		if (!EVP_DigestUpdate(ctx, msg->buf, (u_int)msg->len)) {
			msyslog(LOG_ERR, "MAC encrypt: MAC %s Digest Update data failed.",
				OBJ_nid2sn(ktype));
			goto mac_fail;
		}
		if (!EVP_DigestFinal(ctx, digest->buf, &uilen)) {
			msyslog(LOG_ERR, "MAC encrypt: MAC %s Digest Final failed.",
				OBJ_nid2sn(ktype));
			uilen = 0;
		}
	  mac_fail:
		retlen = (size_t)uilen;
		
		if (ctx)
			EVP_MD_CTX_free(ctx);
	}

#else /* !OPENSSL follows */
	
	if (ktype == NID_md5)
	{
		EVP_MD_CTX *	ctx   = EVP_MD_CTX_new();
		u_int		uilen = 0;

		if (digest->len < 16) {
			msyslog(LOG_ERR, "%s", "MAC encrypt: MAC md5 buf too small.");
		}
		else if ( ! ctx) {
			msyslog(LOG_ERR, "%s", "MAC encrypt: MAC md5 Digest CTX new failed.");
		}
		else {
			EVP_DigestInit(ctx, EVP_get_digestbynid(ktype));
			EVP_DigestUpdate(ctx, key->buf, key->len);
			EVP_DigestUpdate(ctx, msg->buf, msg->len);
			EVP_DigestFinal(ctx, digest->buf, &uilen);
		}
		if (ctx)
			EVP_MD_CTX_free(ctx);
		retlen = (size_t)uilen;
	}
	else
	{
		msyslog(LOG_ERR, "MAC encrypt: invalid key type %d"  , ktype);
	}
	
#endif /* !OPENSSL */

	return retlen;
}
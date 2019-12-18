#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  const u_char ;
struct hmac_ctx {int dummy; } ;
struct TYPE_3__ {int sc_flags; int sc_ealgo; int /*<<< orphan*/  sc_ivkey; int /*<<< orphan*/  sc_ivctx; int /*<<< orphan*/  sc_ekey; int /*<<< orphan*/  sc_mkey; } ;
struct TYPE_4__ {scalar_t__ md_iterations; int /*<<< orphan*/  const* md_salt; } ;
struct geli_dev {char* name; TYPE_1__ sc; TYPE_2__ md; } ;
typedef  int /*<<< orphan*/  mkey ;
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  dkey ;

/* Variables and functions */
#define  CRYPTO_AES_XTS 128 
 int G_ELI_DATAIVKEYLEN ; 
 int G_ELI_DATAKEYLEN ; 
 int G_ELI_FLAG_AUTH ; 
 int /*<<< orphan*/  G_ELI_MAXKEYLEN ; 
 int G_ELI_USERKEYLEN ; 
 int /*<<< orphan*/  SHA256_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA256_Update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  g_eli_crypto_hmac (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_eli_crypto_hmac_final (struct hmac_ctx*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_eli_crypto_hmac_init (struct hmac_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_eli_crypto_hmac_update (struct hmac_ctx*,int /*<<< orphan*/  const*,int) ; 
 int g_eli_mkey_decrypt_any (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  geli_add_key (int /*<<< orphan*/  const*) ; 
 scalar_t__ geli_findkey (struct geli_dev*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  pkcs5v2_genkey (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int,char const*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
geli_probe(struct geli_dev *gdev, const char *passphrase, u_char *mkeyp)
{
	u_char key[G_ELI_USERKEYLEN], mkey[G_ELI_DATAIVKEYLEN], *mkp;
	u_int keynum;
	struct hmac_ctx ctx;
	int error;

	if (mkeyp != NULL) {
		memcpy(&mkey, mkeyp, G_ELI_DATAIVKEYLEN);
		explicit_bzero(mkeyp, G_ELI_DATAIVKEYLEN);
		goto found_key;
	}

	if (geli_findkey(gdev, mkey) == 0) {
		goto found_key;
	}

	g_eli_crypto_hmac_init(&ctx, NULL, 0);
	/*
	 * Prepare Derived-Key from the user passphrase.
	 */
	if (gdev->md.md_iterations < 0) {
		/* XXX TODO: Support loading key files. */
		return (1);
	} else if (gdev->md.md_iterations == 0) {
		g_eli_crypto_hmac_update(&ctx, gdev->md.md_salt,
		    sizeof(gdev->md.md_salt));
		g_eli_crypto_hmac_update(&ctx, (const uint8_t *)passphrase,
		    strlen(passphrase));
	} else if (gdev->md.md_iterations > 0) {
		printf("Calculating GELI Decryption Key for %s %d"
		    " iterations...\n", gdev->name, gdev->md.md_iterations);
		u_char dkey[G_ELI_USERKEYLEN];

		pkcs5v2_genkey(dkey, sizeof(dkey), gdev->md.md_salt,
		    sizeof(gdev->md.md_salt), passphrase,
		    gdev->md.md_iterations);
		g_eli_crypto_hmac_update(&ctx, dkey, sizeof(dkey));
		explicit_bzero(dkey, sizeof(dkey));
	}

	g_eli_crypto_hmac_final(&ctx, key, 0);

	error = g_eli_mkey_decrypt_any(&gdev->md, key, mkey, &keynum);
	if (error == -1) {
		explicit_bzero(mkey, sizeof(mkey));
		explicit_bzero(key, sizeof(key));
		printf("Bad GELI key: bad password?\n");
		return (error);
	} else if (error != 0) {
		explicit_bzero(mkey, sizeof(mkey));
		explicit_bzero(key, sizeof(key));
		printf("Failed to decrypt GELI master key: %d\n", error);
		return (error);
	} else {
		/* Add key to keychain */
		geli_add_key(key);
		explicit_bzero(&key, sizeof(key));
	}

found_key:
	/* Store the keys */
	bcopy(mkey, gdev->sc.sc_mkey, sizeof(gdev->sc.sc_mkey));
	bcopy(mkey, gdev->sc.sc_ivkey, sizeof(gdev->sc.sc_ivkey));
	mkp = mkey + sizeof(gdev->sc.sc_ivkey);
	if ((gdev->sc.sc_flags & G_ELI_FLAG_AUTH) == 0) {
		bcopy(mkp, gdev->sc.sc_ekey, G_ELI_DATAKEYLEN);
	} else {
		/*
		 * The encryption key is: ekey = HMAC_SHA512(Data-Key, 0x10)
		 */
		g_eli_crypto_hmac(mkp, G_ELI_MAXKEYLEN, (const uint8_t *)"\x10", 1,
		    gdev->sc.sc_ekey, 0);
	}
	explicit_bzero(mkey, sizeof(mkey));

	/* Initialize the per-sector IV. */
	switch (gdev->sc.sc_ealgo) {
	case CRYPTO_AES_XTS:
		break;
	default:
		SHA256_Init(&gdev->sc.sc_ivctx);
		SHA256_Update(&gdev->sc.sc_ivctx, gdev->sc.sc_ivkey,
		    sizeof(gdev->sc.sc_ivkey));
		break;
	}

	return (0);
}
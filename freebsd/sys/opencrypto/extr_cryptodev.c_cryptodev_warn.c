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
struct timeval {int dummy; } ;
struct csession {int cipher; int mac; } ;

/* Variables and functions */
#define  CRYPTO_3DES_CBC 134 
#define  CRYPTO_ARC4 133 
#define  CRYPTO_BLF_CBC 132 
#define  CRYPTO_CAST_CBC 131 
#define  CRYPTO_DES_CBC 130 
#define  CRYPTO_MD5_HMAC 129 
#define  CRYPTO_SKIPJACK_CBC 128 
 int /*<<< orphan*/  gone_in (int,char*) ; 
 int /*<<< orphan*/  ratecheck (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warninterval ; 

__attribute__((used)) static void
cryptodev_warn(struct csession *cse)
{
	static struct timeval arc4warn, blfwarn, castwarn, deswarn, md5warn;
	static struct timeval skipwarn, tdeswarn;

	switch (cse->cipher) {
	case CRYPTO_DES_CBC:
		if (ratecheck(&deswarn, &warninterval))
			gone_in(13, "DES cipher via /dev/crypto");
		break;
	case CRYPTO_3DES_CBC:
		if (ratecheck(&tdeswarn, &warninterval))
			gone_in(13, "3DES cipher via /dev/crypto");
		break;
	case CRYPTO_BLF_CBC:
		if (ratecheck(&blfwarn, &warninterval))
			gone_in(13, "Blowfish cipher via /dev/crypto");
		break;
	case CRYPTO_CAST_CBC:
		if (ratecheck(&castwarn, &warninterval))
			gone_in(13, "CAST128 cipher via /dev/crypto");
		break;
	case CRYPTO_SKIPJACK_CBC:
		if (ratecheck(&skipwarn, &warninterval))
			gone_in(13, "Skipjack cipher via /dev/crypto");
		break;
	case CRYPTO_ARC4:
		if (ratecheck(&arc4warn, &warninterval))
			gone_in(13, "ARC4 cipher via /dev/crypto");
		break;
	}

	switch (cse->mac) {
	case CRYPTO_MD5_HMAC:
		if (ratecheck(&md5warn, &warninterval))
			gone_in(13, "MD5-HMAC authenticator via /dev/crypto");
		break;
	}
}
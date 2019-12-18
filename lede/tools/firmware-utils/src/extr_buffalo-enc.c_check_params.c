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

/* Variables and functions */
 scalar_t__ BCRYPT_MAX_KEYLEN ; 
 int ENC_MAGIC_LEN ; 
 int ENC_PRODUCT_LEN ; 
 int ENC_VERSION_LEN ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/ * crypt_key ; 
 int /*<<< orphan*/  do_decrypt ; 
 int /*<<< orphan*/ * ifname ; 
 int /*<<< orphan*/ * magic ; 
 int /*<<< orphan*/ * ofname ; 
 int /*<<< orphan*/ * product ; 
 int strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * version ; 

__attribute__((used)) static int check_params(void)
{
	int ret = -1;

	if (ifname == NULL) {
		ERR("no input file specified");
		goto out;
	}

	if (ofname == NULL) {
		ERR("no output file specified");
		goto out;
	}

	if (crypt_key == NULL) {
		ERR("no key specified");
		goto out;
	} else if (strlen(crypt_key) > BCRYPT_MAX_KEYLEN) {
		ERR("key '%s' is too long", crypt_key);
		goto out;
	}

	if (strlen(magic) != (ENC_MAGIC_LEN - 1)) {
		ERR("length of magic must be %d", ENC_MAGIC_LEN - 1);
		goto out;
	}

	if (!do_decrypt) {
		if (product == NULL) {
			ERR("no product specified");
			goto out;
		}

		if (version == NULL) {
			ERR("no version specified");
			goto out;
		}

		if (strlen(product) > (ENC_PRODUCT_LEN - 1)) {
			ERR("product name '%s' is too long", product);
			goto out;
		}

		if (strlen(version) > (ENC_VERSION_LEN - 1)) {
			ERR("version '%s' is too long", version);
			goto out;
		}
	}

	ret = 0;

out:
	return ret;
}
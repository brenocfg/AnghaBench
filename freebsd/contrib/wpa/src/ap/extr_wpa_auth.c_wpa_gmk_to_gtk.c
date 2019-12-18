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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  WPA_GMK_LEN ; 
 int WPA_GTK_MAX_LEN ; 
 int WPA_NONCE_LEN ; 
 int /*<<< orphan*/  forced_memzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ sha1_prf (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ sha256_prf (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ sha384_prf (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_get_ntp_timestamp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wpa_gmk_to_gtk(const u8 *gmk, const char *label, const u8 *addr,
			  const u8 *gnonce, u8 *gtk, size_t gtk_len)
{
	u8 data[ETH_ALEN + WPA_NONCE_LEN + 8 + WPA_GTK_MAX_LEN];
	u8 *pos;
	int ret = 0;

	/* GTK = PRF-X(GMK, "Group key expansion",
	 *	AA || GNonce || Time || random data)
	 * The example described in the IEEE 802.11 standard uses only AA and
	 * GNonce as inputs here. Add some more entropy since this derivation
	 * is done only at the Authenticator and as such, does not need to be
	 * exactly same.
	 */
	os_memset(data, 0, sizeof(data));
	os_memcpy(data, addr, ETH_ALEN);
	os_memcpy(data + ETH_ALEN, gnonce, WPA_NONCE_LEN);
	pos = data + ETH_ALEN + WPA_NONCE_LEN;
	wpa_get_ntp_timestamp(pos);
#ifdef TEST_FUZZ
	os_memset(pos, 0xef, 8);
#endif /* TEST_FUZZ */
	pos += 8;
	if (random_get_bytes(pos, gtk_len) < 0)
		ret = -1;

#ifdef CONFIG_SHA384
	if (sha384_prf(gmk, WPA_GMK_LEN, label, data, sizeof(data),
		       gtk, gtk_len) < 0)
		ret = -1;
#else /* CONFIG_SHA384 */
#ifdef CONFIG_SHA256
	if (sha256_prf(gmk, WPA_GMK_LEN, label, data, sizeof(data),
		       gtk, gtk_len) < 0)
		ret = -1;
#else /* CONFIG_SHA256 */
	if (sha1_prf(gmk, WPA_GMK_LEN, label, data, sizeof(data),
		     gtk, gtk_len) < 0)
		ret = -1;
#endif /* CONFIG_SHA256 */
#endif /* CONFIG_SHA384 */

	forced_memzero(data, sizeof(data));

	return ret;
}
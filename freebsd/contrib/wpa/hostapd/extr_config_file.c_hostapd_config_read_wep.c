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
struct hostapd_wep_keys {size_t* len; scalar_t__ keys_set; int /*<<< orphan*/ ** key; } ;

/* Variables and functions */
 int NUM_WEP_KEYS ; 
 int /*<<< orphan*/  bin_clear_free (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ hexstr2bin (char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/ * os_memdup (char*,size_t) ; 
 size_t os_strlen (char*) ; 

__attribute__((used)) static int hostapd_config_read_wep(struct hostapd_wep_keys *wep, int keyidx,
				   char *val)
{
	size_t len = os_strlen(val);

	if (keyidx < 0 || keyidx > 3)
		return -1;

	if (len == 0) {
		int i, set = 0;

		bin_clear_free(wep->key[keyidx], wep->len[keyidx]);
		wep->key[keyidx] = NULL;
		wep->len[keyidx] = 0;
		for (i = 0; i < NUM_WEP_KEYS; i++) {
			if (wep->key[i])
				set++;
		}
		if (!set)
			wep->keys_set = 0;
		return 0;
	}

	if (wep->key[keyidx] != NULL)
		return -1;

	if (val[0] == '"') {
		if (len < 2 || val[len - 1] != '"')
			return -1;
		len -= 2;
		wep->key[keyidx] = os_memdup(val + 1, len);
		if (wep->key[keyidx] == NULL)
			return -1;
		wep->len[keyidx] = len;
	} else {
		if (len & 1)
			return -1;
		len /= 2;
		wep->key[keyidx] = os_malloc(len);
		if (wep->key[keyidx] == NULL)
			return -1;
		wep->len[keyidx] = len;
		if (hexstr2bin(val, wep->key[keyidx], len) < 0)
			return -1;
	}

	wep->keys_set++;

	return 0;
}
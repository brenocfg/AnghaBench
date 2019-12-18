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
 int WPA_CIPHER_AES_128_CMAC ; 
 int WPA_CIPHER_BIP_CMAC_256 ; 
 int WPA_CIPHER_BIP_GMAC_128 ; 
 int WPA_CIPHER_BIP_GMAC_256 ; 
 int WPA_CIPHER_CCMP ; 
 int WPA_CIPHER_CCMP_256 ; 
 int WPA_CIPHER_GCMP ; 
 int WPA_CIPHER_GCMP_256 ; 
 int WPA_CIPHER_GTK_NOT_USED ; 
 int WPA_CIPHER_NONE ; 
 int WPA_CIPHER_TKIP ; 
 int WPA_CIPHER_WEP104 ; 
 int WPA_CIPHER_WEP40 ; 
 int /*<<< orphan*/  os_free (char*) ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 char* os_strdup (char const*) ; 

int wpa_parse_cipher(const char *value)
{
	int val = 0, last;
	char *start, *end, *buf;

	buf = os_strdup(value);
	if (buf == NULL)
		return -1;
	start = buf;

	while (*start != '\0') {
		while (*start == ' ' || *start == '\t')
			start++;
		if (*start == '\0')
			break;
		end = start;
		while (*end != ' ' && *end != '\t' && *end != '\0')
			end++;
		last = *end == '\0';
		*end = '\0';
		if (os_strcmp(start, "CCMP-256") == 0)
			val |= WPA_CIPHER_CCMP_256;
		else if (os_strcmp(start, "GCMP-256") == 0)
			val |= WPA_CIPHER_GCMP_256;
		else if (os_strcmp(start, "CCMP") == 0)
			val |= WPA_CIPHER_CCMP;
		else if (os_strcmp(start, "GCMP") == 0)
			val |= WPA_CIPHER_GCMP;
		else if (os_strcmp(start, "TKIP") == 0)
			val |= WPA_CIPHER_TKIP;
		else if (os_strcmp(start, "WEP104") == 0)
			val |= WPA_CIPHER_WEP104;
		else if (os_strcmp(start, "WEP40") == 0)
			val |= WPA_CIPHER_WEP40;
		else if (os_strcmp(start, "NONE") == 0)
			val |= WPA_CIPHER_NONE;
		else if (os_strcmp(start, "GTK_NOT_USED") == 0)
			val |= WPA_CIPHER_GTK_NOT_USED;
		else if (os_strcmp(start, "AES-128-CMAC") == 0)
			val |= WPA_CIPHER_AES_128_CMAC;
		else if (os_strcmp(start, "BIP-GMAC-128") == 0)
			val |= WPA_CIPHER_BIP_GMAC_128;
		else if (os_strcmp(start, "BIP-GMAC-256") == 0)
			val |= WPA_CIPHER_BIP_GMAC_256;
		else if (os_strcmp(start, "BIP-CMAC-256") == 0)
			val |= WPA_CIPHER_BIP_CMAC_256;
		else {
			os_free(buf);
			return -1;
		}

		if (last)
			break;
		start = end + 1;
	}
	os_free(buf);

	return val;
}
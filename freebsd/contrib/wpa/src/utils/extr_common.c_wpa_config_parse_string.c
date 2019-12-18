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
typedef  char u8 ;

/* Variables and functions */
 char* dup_binstr (char const*,size_t) ; 
 scalar_t__ hexstr2bin (char const*,char*,size_t) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (size_t) ; 
 size_t os_strlen (char const*) ; 
 char* os_strrchr (char const*,char) ; 
 size_t printf_decode (char*,size_t,char*) ; 

char * wpa_config_parse_string(const char *value, size_t *len)
{
	if (*value == '"') {
		const char *pos;
		char *str;
		value++;
		pos = os_strrchr(value, '"');
		if (pos == NULL || pos[1] != '\0')
			return NULL;
		*len = pos - value;
		str = dup_binstr(value, *len);
		if (str == NULL)
			return NULL;
		return str;
	} else if (*value == 'P' && value[1] == '"') {
		const char *pos;
		char *tstr, *str;
		size_t tlen;
		value += 2;
		pos = os_strrchr(value, '"');
		if (pos == NULL || pos[1] != '\0')
			return NULL;
		tlen = pos - value;
		tstr = dup_binstr(value, tlen);
		if (tstr == NULL)
			return NULL;

		str = os_malloc(tlen + 1);
		if (str == NULL) {
			os_free(tstr);
			return NULL;
		}

		*len = printf_decode((u8 *) str, tlen + 1, tstr);
		os_free(tstr);

		return str;
	} else {
		u8 *str;
		size_t tlen, hlen = os_strlen(value);
		if (hlen & 1)
			return NULL;
		tlen = hlen / 2;
		str = os_malloc(tlen + 1);
		if (str == NULL)
			return NULL;
		if (hexstr2bin(value, str, tlen)) {
			os_free(str);
			return NULL;
		}
		str[tlen] = '\0';
		*len = tlen;
		return (char *) str;
	}
}
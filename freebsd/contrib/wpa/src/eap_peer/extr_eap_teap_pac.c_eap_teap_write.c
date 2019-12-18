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

/* Variables and functions */
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_realloc (char*,size_t) ; 
 int os_snprintf (char*,int,char*,...) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 size_t os_strlen (char const*) ; 
 int /*<<< orphan*/  wpa_snprintf_hex (char*,int,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static void eap_teap_write(char **buf, char **pos, size_t *buf_len,
			   const char *field, const u8 *data,
			   size_t len, int txt)
{
	size_t i, need;
	int ret;
	char *end;

	if (!data || !buf || !(*buf) || !pos || !(*pos) || *pos < *buf)
		return;

	need = os_strlen(field) + len * 2 + 30;
	if (txt)
		need += os_strlen(field) + len + 20;

	if (*pos - *buf + need > *buf_len) {
		char *nbuf = os_realloc(*buf, *buf_len + need);

		if (!nbuf) {
			os_free(*buf);
			*buf = NULL;
			return;
		}
		*pos = nbuf + (*pos - *buf);
		*buf = nbuf;
		*buf_len += need;
	}
	end = *buf + *buf_len;

	ret = os_snprintf(*pos, end - *pos, "%s=", field);
	if (os_snprintf_error(end - *pos, ret))
		return;
	*pos += ret;
	*pos += wpa_snprintf_hex(*pos, end - *pos, data, len);
	ret = os_snprintf(*pos, end - *pos, "\n");
	if (os_snprintf_error(end - *pos, ret))
		return;
	*pos += ret;

	if (txt) {
		ret = os_snprintf(*pos, end - *pos, "%s-txt=", field);
		if (os_snprintf_error(end - *pos, ret))
			return;
		*pos += ret;
		for (i = 0; i < len; i++) {
			ret = os_snprintf(*pos, end - *pos, "%c", data[i]);
			if (os_snprintf_error(end - *pos, ret))
				return;
			*pos += ret;
		}
		ret = os_snprintf(*pos, end - *pos, "\n");
		if (os_snprintf_error(end - *pos, ret))
			return;
		*pos += ret;
	}
}
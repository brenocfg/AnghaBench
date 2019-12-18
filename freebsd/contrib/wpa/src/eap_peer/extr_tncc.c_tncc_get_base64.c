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
 int /*<<< orphan*/  MSG_DEBUG ; 
 unsigned char* base64_decode (unsigned char*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  os_strlen (char*) ; 
 char* os_strstr (char*,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static unsigned char * tncc_get_base64(char *start, size_t *decoded_len)
{
	char *pos, *pos2;
	unsigned char *decoded;

	pos = os_strstr(start, "<Base64>");
	if (pos == NULL)
		return NULL;

	pos += 8;
	pos2 = os_strstr(pos, "</Base64>");
	if (pos2 == NULL)
		return NULL;
	*pos2 = '\0';

	decoded = base64_decode((unsigned char *) pos, os_strlen(pos),
				decoded_len);
	*pos2 = '<';
	if (decoded == NULL) {
		wpa_printf(MSG_DEBUG, "TNC: Failed to decode Base64 data");
	}

	return decoded;
}
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
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_zalloc (int) ; 
 scalar_t__ wpa_write_ciphers (char*,char*,int,char*) ; 

__attribute__((used)) static char * wpa_config_write_cipher(int cipher)
{
#ifdef CONFIG_NO_WPA
	return NULL;
#else /* CONFIG_NO_WPA */
	char *buf = os_zalloc(50);
	if (buf == NULL)
		return NULL;

	if (wpa_write_ciphers(buf, buf + 50, cipher, " ") < 0) {
		os_free(buf);
		return NULL;
	}

	return buf;
#endif /* CONFIG_NO_WPA */
}
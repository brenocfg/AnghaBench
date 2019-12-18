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
struct hostapd_bss_config {int /*<<< orphan*/  radius_das_shared_secret_len; int /*<<< orphan*/ * radius_das_shared_secret; int /*<<< orphan*/  radius_das_client_addr; } ;

/* Variables and functions */
 scalar_t__ hostapd_parse_ip_addr (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 char* os_strchr (char*,char) ; 
 scalar_t__ os_strdup (char*) ; 
 int /*<<< orphan*/  os_strlen (char*) ; 

__attribute__((used)) static int hostapd_parse_das_client(struct hostapd_bss_config *bss, char *val)
{
	char *secret;

	secret = os_strchr(val, ' ');
	if (secret == NULL)
		return -1;

	*secret++ = '\0';

	if (hostapd_parse_ip_addr(val, &bss->radius_das_client_addr))
		return -1;

	os_free(bss->radius_das_shared_secret);
	bss->radius_das_shared_secret = (u8 *) os_strdup(secret);
	if (bss->radius_das_shared_secret == NULL)
		return -1;
	bss->radius_das_shared_secret_len = os_strlen(secret);

	return 0;
}
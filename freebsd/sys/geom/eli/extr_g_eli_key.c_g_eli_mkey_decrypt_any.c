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
struct g_eli_metadata {int dummy; } ;

/* Variables and functions */
 int G_ELI_MAXMKEYS ; 
 int g_eli_mkey_decrypt (struct g_eli_metadata const*,unsigned char const*,unsigned char*,int) ; 

int
g_eli_mkey_decrypt_any(const struct g_eli_metadata *md,
    const unsigned char *key, unsigned char *mkey, unsigned *nkeyp)
{
	int error, nkey;

	if (nkeyp != NULL)
		*nkeyp = -1;

	error = -1;
	for (nkey = 0; nkey < G_ELI_MAXMKEYS; nkey++) {
		error = g_eli_mkey_decrypt(md, key, mkey, nkey);
		if (error == 0) {
			if (nkeyp != NULL)
				*nkeyp = nkey;
			break;
		} else if (error > 0) {
			break;
		}
	}

	return (error);
}
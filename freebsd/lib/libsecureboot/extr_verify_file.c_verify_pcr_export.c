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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  hexbuf ;
typedef  int /*<<< orphan*/  hbuf ;

/* Variables and functions */
 int br_sha256_SIZE ; 
 char* hexdigest (char*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int ve_pcr_get (unsigned char*,int) ; 

void
verify_pcr_export(void)
{
#ifdef VE_PCR_SUPPORT
	char hexbuf[br_sha256_SIZE * 2 + 2];
	unsigned char hbuf[br_sha256_SIZE];
	char *hex;
	ssize_t hlen;

	hlen = ve_pcr_get(hbuf, sizeof(hbuf));
	if (hlen > 0) {
		hex = hexdigest(hexbuf, sizeof(hexbuf), hbuf, hlen);
		if (hex) {
			hex[hlen*2] = '\0'; /* clobber newline */
			setenv("loader.ve.pcr", hex, 1);
		}
	}
#endif
}
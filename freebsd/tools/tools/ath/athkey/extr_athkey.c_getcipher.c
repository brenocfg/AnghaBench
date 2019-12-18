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
 int HAL_CIPHER_AES_CCM ; 
 int HAL_CIPHER_AES_OCB ; 
 int HAL_CIPHER_CKIP ; 
 int HAL_CIPHER_CLR ; 
 int HAL_CIPHER_TKIP ; 
 int HAL_CIPHER_WEP ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ streq (char const*,char*) ; 

__attribute__((used)) static int
getcipher(const char *name)
{
#define	streq(a,b)	(strcasecmp(a,b) == 0)

	if (streq(name, "wep"))
		return HAL_CIPHER_WEP;
	if (streq(name, "tkip"))
		return HAL_CIPHER_TKIP;
	if (streq(name, "aes-ocb") || streq(name, "ocb"))
		return HAL_CIPHER_AES_OCB;
	if (streq(name, "aes-ccm") || streq(name, "ccm") ||
	    streq(name, "aes"))
		return HAL_CIPHER_AES_CCM;
	if (streq(name, "ckip"))
		return HAL_CIPHER_CKIP;
	if (streq(name, "none") || streq(name, "clr"))
		return HAL_CIPHER_CLR;

	fprintf(stderr, "%s: unknown cipher %s\n", progname, name);
	exit(-1);
#undef streq
}
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
 int CRYPTO_MAX_ALG_NAME ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* strchr (char const*,char) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static bool parse_cipher_name(char *essiv_cipher_name, const char *cra_name)
{
	const char *p, *q;
	int len;

	/* find the last opening parens */
	p = strrchr(cra_name, '(');
	if (!p++)
		return false;

	/* find the first closing parens in the tail of the string */
	q = strchr(p, ')');
	if (!q)
		return false;

	len = q - p;
	if (len >= CRYPTO_MAX_ALG_NAME)
		return false;

	memcpy(essiv_cipher_name, p, len);
	essiv_cipher_name[len] = '\0';
	return true;
}
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
struct alg {int dummy; } ;

/* Variables and functions */
 struct alg* build_authenc (struct alg*,struct alg*) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 struct alg* find_alg (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strchr (char const*,char) ; 
 char* strndup (char const*,int) ; 

__attribute__((used)) static struct alg *
build_authenc_name(const char *name)
{
	struct alg *cipher, *hmac;
	const char *hmac_name;
	char *cp, *cipher_name;

	cp = strchr(name, '+');
	cipher_name = strndup(name, cp - name);
	hmac_name = cp + 1;
	cipher = find_alg(cipher_name);
	free(cipher_name);
	if (cipher == NULL)
		errx(1, "Invalid cipher %s", cipher_name);
	hmac = find_alg(hmac_name);
	if (hmac == NULL)
		errx(1, "Invalid hash %s", hmac_name);
	return (build_authenc(cipher, hmac));
}
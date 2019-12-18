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
 char* bigcrypt (char const*,char const*) ; 
 char* crypt (char const*,char const*) ; 
 scalar_t__ is_md5_salt (char const*) ; 
 scalar_t__ iscomsec () ; 
 char* md5_crypt (char const*,char const*) ; 
 char* pick_salt () ; 

char *
xcrypt(const char *password, const char *salt)
{
	char *crypted;

	/*
	 * If we don't have a salt we are encrypting a fake password for
	 * for timing purposes.  Pick an appropriate salt.
	 */
	if (salt == NULL)
		salt = pick_salt();

# ifdef HAVE_MD5_PASSWORDS
	if (is_md5_salt(salt))
		crypted = md5_crypt(password, salt);
	else
		crypted = crypt(password, salt);
# elif defined(__hpux) && !defined(HAVE_SECUREWARE)
	if (iscomsec())
		crypted = bigcrypt(password, salt);
	else
		crypted = crypt(password, salt);
# elif defined(HAVE_SECUREWARE)
	crypted = bigcrypt(password, salt);
# else
	crypted = crypt(password, salt);
# endif

	return crypted;
}
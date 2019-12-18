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
struct passwd {char* pw_passwd; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTH_KRB5 ; 
 int /*<<< orphan*/  AUTH_OTP ; 
 int /*<<< orphan*/  auth ; 
 int /*<<< orphan*/  crypt (char const*,char*) ; 
 scalar_t__ krb5_verify (struct passwd*,char const*) ; 
 scalar_t__ otp_verify (struct passwd*,char const*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
check_password(struct passwd *pwd, const char *password)
{
    if(pwd->pw_passwd == NULL)
	return 1;
    if(pwd->pw_passwd[0] == '\0'){
#ifdef ALLOW_NULL_PASSWORD
	return password[0] != '\0';
#else
	return 1;
#endif
    }
    if(strcmp(pwd->pw_passwd, crypt(password, pwd->pw_passwd)) == 0)
	return 0;
#ifdef KRB5
    if(krb5_verify(pwd, password) == 0) {
	auth = AUTH_KRB5;
	return 0;
    }
#endif
#ifdef OTP
    if (otp_verify (pwd, password) == 0) {
       auth = AUTH_OTP;
       return 0;
    }
#endif
    return 1;
}
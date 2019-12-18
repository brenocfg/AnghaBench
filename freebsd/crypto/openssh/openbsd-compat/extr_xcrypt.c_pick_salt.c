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
struct passwd {int dummy; } ;
typedef  int /*<<< orphan*/  salt ;

/* Variables and functions */
 int MIN (size_t,int) ; 
 int /*<<< orphan*/  endpwent () ; 
 int /*<<< orphan*/  explicit_bzero (char*,int /*<<< orphan*/ ) ; 
 struct passwd* getpwent () ; 
 int /*<<< orphan*/  setpwent () ; 
 char* shadow_pw (struct passwd*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static const char *
pick_salt(void)
{
	struct passwd *pw;
	char *passwd, *p;
	size_t typelen;
	static char salt[32];

	if (salt[0] != '\0')
		return salt;
	strlcpy(salt, "xx", sizeof(salt));
	setpwent();
	while ((pw = getpwent()) != NULL) {
		passwd = shadow_pw(pw);
		if (passwd[0] == '$' && (p = strrchr(passwd+1, '$')) != NULL) {
			typelen = p - passwd + 1;
			strlcpy(salt, passwd, MIN(typelen, sizeof(salt)));
			explicit_bzero(passwd, strlen(passwd));
			goto out;
		}
	}
 out:
	endpwent();
	return salt;
}
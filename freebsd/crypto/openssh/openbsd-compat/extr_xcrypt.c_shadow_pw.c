#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct spwd {char* sp_pwdp; } ;
struct TYPE_2__ {char* fd_encrypt; } ;
struct pr_passwd {TYPE_1__ ufld; } ;
struct passwd_adjunct {char* pwa_passwd; } ;
struct passwd {char* pw_passwd; int /*<<< orphan*/  pw_name; } ;

/* Variables and functions */
 char* get_iaf_password (struct passwd*) ; 
 struct pr_passwd* getprpwnam (int /*<<< orphan*/ ) ; 
 struct passwd_adjunct* getpwanam (int /*<<< orphan*/ ) ; 
 struct spwd* getspnam (int /*<<< orphan*/ ) ; 
 scalar_t__ issecure () ; 

char *
shadow_pw(struct passwd *pw)
{
	char *pw_password = pw->pw_passwd;

# if defined(HAVE_SHADOW_H) && !defined(DISABLE_SHADOW)
	struct spwd *spw = getspnam(pw->pw_name);

	if (spw != NULL)
		pw_password = spw->sp_pwdp;
# endif

#ifdef USE_LIBIAF
	return(get_iaf_password(pw));
#endif

# if defined(HAVE_GETPWANAM) && !defined(DISABLE_SHADOW)
	struct passwd_adjunct *spw;
	if (issecure() && (spw = getpwanam(pw->pw_name)) != NULL)
		pw_password = spw->pwa_passwd;
# elif defined(HAVE_SECUREWARE)
	struct pr_passwd *spw = getprpwnam(pw->pw_name);

	if (spw != NULL)
		pw_password = spw->ufld.fd_encrypt;
# endif

	return pw_password;
}
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
struct passwd {char* pw_dir; char* pw_name; } ;

/* Variables and functions */
 char* malloc (int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 char* strcpy (char*,char const*) ; 
 int /*<<< orphan*/  strcspn (char*,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *
substvar(const char * var, const struct passwd * pwd, int hlen, int pch, int nlen)
{
    char    *np = NULL;

    if (var != NULL) {
	int	tildes = 0;
	int	dollas = 0;
	char	*p;
	const char *q;

	if (pwd != NULL) {
	    for (q = var; *q != '\0'; ++q) {
		tildes += (*q == '~');
		dollas += (*q == '$');
	    }
	}

	np = malloc(strlen(var) + (dollas * nlen)
		    - dollas + (tildes * (pch+hlen))
		    - tildes + 1);

	if (np != NULL) {
	    p = strcpy(np, var);

	    if (pwd != NULL) {
		/*
		 * This loop does user username and homedir substitutions
		 * for unescaped $ (username) and ~ (homedir)
		 */
		while (*(p += strcspn(p, "~$")) != '\0') {
		    int	l = strlen(p);

		    if (p > np && *(p-1) == '\\')  /* Escaped: */
			memmove(p - 1, p, l + 1); /* Slide-out the backslash */
		    else if (*p == '~') {
			int	v = pch && *(p+1) != '/'; /* Avoid double // */
			memmove(p + hlen + v, p + 1, l);  /* Subst homedir */
			memmove(p, pwd->pw_dir, hlen);
			if (v)
			    p[hlen] = '/';
			p += hlen + v;
		    }
		    else /* if (*p == '$') */ {
			memmove(p + nlen, p + 1, l);	/* Subst username */
			memmove(p, pwd->pw_name, nlen);
			p += nlen;
		    }
		}
	    }
	}
    }

    return (np);
}
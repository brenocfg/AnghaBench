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
 int ENOENT ; 
#define  FBACK_MDENV 130 
#define  FBACK_STATIC 129 
#define  FBACK_STENV 128 
 int /*<<< orphan*/  _res_checkenv (char*) ; 
 scalar_t__ hintenv_merged ; 
 int /*<<< orphan*/  kenv_lock ; 
 char** kenvp ; 
 char* kern_envp ; 
 char* md_envp ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int sscanf (char const*,char*,char*,int*,char*,char*) ; 
 char* static_hints ; 
 int stenv_skip ; 
 int sthints_skip ; 
 void* strchr (char const*,char) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int
res_find(char **hintp_cookie, int *line, int *startln,
    const char *name, int *unit, const char *resname, const char *value,
    const char **ret_name, int *ret_namelen, int *ret_unit,
    const char **ret_resname, int *ret_resnamelen, const char **ret_value)
{
	int fbacklvl = FBACK_MDENV, i = 0, n = 0;
	char r_name[32];
	int r_unit;
	char r_resname[32];
	char r_value[128];
	const char *s, *cp;
	char *hintp, *p;
	bool dyn_used = false;


	/*
	 * We are expecting that the caller will pass us a hintp_cookie that
	 * they are tracking.  Upon entry, if *hintp_cookie is *not* set, this
	 * indicates to us that we should be figuring out based on the current
	 * environment where to search.  This keeps us sane throughout the
	 * entirety of a single search.
	 */
	if (*hintp_cookie == NULL) {
		hintp = NULL;
		if (hintenv_merged) {
			/*
			 * static_hints, if it was previously used, has
			 * already been folded in to the environment
			 * by this point.
			 */
			mtx_lock(&kenv_lock);
			cp = kenvp[0];
			for (i = 0; cp != NULL; cp = kenvp[++i]) {
				if (!strncmp(cp, "hint.", 5)) {
					hintp = kenvp[0];
					break;
				}
			}
			mtx_unlock(&kenv_lock);
			dyn_used = true;
		} else {
			/*
			 * We'll have a chance to keep coming back here until
			 * we've actually exhausted all of our possibilities.
			 * We might have chosen the MD/Static env because it
			 * had some kind of hints, but perhaps it didn't have
			 * the hint we are looking for.  We don't provide any
			 * fallback when searching the dynamic environment.
			 */
fallback:
			if (dyn_used || fbacklvl >= FBACK_STATIC)
				return (ENOENT);

			switch (fbacklvl) {
			case FBACK_MDENV:
				fbacklvl++;
				if (_res_checkenv(md_envp)) {
					hintp = md_envp;
					break;
				}

				/* FALLTHROUGH */
			case FBACK_STENV:
				fbacklvl++;
				if (!stenv_skip && _res_checkenv(kern_envp)) {
					hintp = kern_envp;
					break;
				} else
					stenv_skip = true;

				/* FALLTHROUGH */
			case FBACK_STATIC:
				fbacklvl++;
				/* We'll fallback to static_hints if needed/can */
				if (!sthints_skip &&
				    _res_checkenv(static_hints))
					hintp = static_hints;
				else
					sthints_skip = true;

				break;
			default:
				return (ENOENT);
			}
		}

		if (hintp == NULL)
			return (ENOENT);
		*hintp_cookie = hintp;
	} else {
		hintp = *hintp_cookie;
		if (hintenv_merged && hintp == kenvp[0])
			dyn_used = true;
		else
			/*
			 * If we aren't using the dynamic environment, we need
			 * to run through the proper fallback procedure again.
			 * This is so that we do continuations right if we're
			 * working with *line and *startln.
			 */
			goto fallback;
	}

	if (dyn_used) {
		mtx_lock(&kenv_lock);
		i = 0;
	}

	cp = hintp;
	while (cp) {
		(*line)++;
		if (strncmp(cp, "hint.", 5) != 0)
			goto nexthint;
		n = sscanf(cp, "hint.%32[^.].%d.%32[^=]=%127s", r_name, &r_unit,
		    r_resname, r_value);
		if (n != 4) {
			printf("CONFIG: invalid hint '%s'\n", cp);
			p = strchr(cp, 'h');
			*p = 'H';
			goto nexthint;
		}
		if (startln && *startln >= 0 && *line < *startln)
			goto nexthint;
		if (name && strcmp(name, r_name) != 0)
			goto nexthint;
		if (unit && *unit != r_unit)
			goto nexthint;
		if (resname && strcmp(resname, r_resname) != 0)
			goto nexthint;
		if (value && strcmp(value, r_value) != 0)
			goto nexthint;
		/* Successfully found a hint matching all criteria */
		break;
nexthint:
		if (dyn_used) {
			cp = kenvp[++i];
			if (cp == NULL)
				break;
		} else {
			while (*cp != '\0')
				cp++;
			cp++;
			if (*cp == '\0') {
				cp = NULL;
				break;
			}
		}
	}
	if (dyn_used)
		mtx_unlock(&kenv_lock);
	if (cp == NULL)
		goto fallback;

	s = cp;
	/* This is a bit of a hack, but at least is reentrant */
	/* Note that it returns some !unterminated! strings. */
	s = strchr(s, '.') + 1;		/* start of device */
	if (ret_name)
		*ret_name = s;
	s = strchr(s, '.') + 1;		/* start of unit */
	if (ret_namelen && ret_name)
		*ret_namelen = s - *ret_name - 1; /* device length */
	if (ret_unit)
		*ret_unit = r_unit;
	s = strchr(s, '.') + 1;		/* start of resname */
	if (ret_resname)
		*ret_resname = s;
	s = strchr(s, '=') + 1;		/* start of value */
	if (ret_resnamelen && ret_resname)
		*ret_resnamelen = s - *ret_resname - 1; /* value len */
	if (ret_value)
		*ret_value = s;
	if (startln)			/* line number for anchor */
		*startln = *line + 1;
	return 0;
}
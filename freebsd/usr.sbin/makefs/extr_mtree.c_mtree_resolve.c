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
struct sbuf {int dummy; } ;

/* Variables and functions */
 void* EINVAL ; 
 void* ENOMEM ; 
 char* ecalloc (int,int) ; 
 void* errno ; 
 char* estrdup (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getcwd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 char const* getprogname () ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  sbuf_bcat (struct sbuf*,char const*,int) ; 
 int /*<<< orphan*/  sbuf_cat (struct sbuf*,char*) ; 
 int /*<<< orphan*/  sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 struct sbuf* sbuf_new_auto () ; 
 int /*<<< orphan*/  sbuf_putc (struct sbuf*,char const) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static char *
mtree_resolve(const char *spec, int *istemp)
{
	struct sbuf *sb;
	char *res, *var = NULL;
	const char *base, *p, *v;
	size_t len;
	int c, error, quoted, subst;

	len = strlen(spec);
	if (len == 0) {
		errno = EINVAL;
		return (NULL);
	}

	c = (len > 1) ? (spec[0] == spec[len - 1]) ? spec[0] : 0 : 0;
	*istemp = (c == '`') ? 1 : 0;
	subst = (c == '`' || c == '"') ? 1 : 0;
	quoted = (subst || c == '\'') ? 1 : 0;

	if (!subst) {
		res = estrdup(spec + quoted);
		if (quoted)
			res[len - 2] = '\0';
		return (res);
	}

	sb = sbuf_new_auto();
	if (sb == NULL) {
		errno = ENOMEM;
		return (NULL);
	}

	base = spec + 1;
	len -= 2;
	error = 0;
	while (len > 0) {
		p = strchr(base, '$');
		if (p == NULL) {
			sbuf_bcat(sb, base, len);
			base += len;
			len = 0;
			continue;
		}
		/* The following is safe. spec always starts with a quote. */
		if (p[-1] == '\\')
			p--;
		if (base != p) {
			sbuf_bcat(sb, base, p - base);
			len -= p - base;
			base = p;
		}
		if (*p == '\\') {
			sbuf_putc(sb, '$');
			base += 2;
			len -= 2;
			continue;
		}
		/* Skip the '$'. */
		base++;
		len--;
		/* Handle ${X} vs $X. */
		v = base;
		if (*base == '{') {
			p = strchr(v, '}');
			if (p == NULL)
				p = v;
		} else
			p = v;
		len -= (p + 1) - base;
		base = p + 1;

		if (v == p) {
			sbuf_putc(sb, *v);
			continue;
		}

		error = ENOMEM;
		var = ecalloc(p - v, 1);
		memcpy(var, v + 1, p - v - 1);
		if (strcmp(var, ".CURDIR") == 0) {
			res = getcwd(NULL, 0);
			if (res == NULL)
				break;
		} else if (strcmp(var, ".PROG") == 0) {
			res = estrdup(getprogname());
		} else {
			v = getenv(var);
			if (v != NULL) {
				res = estrdup(v);
			} else
				res = NULL;
		}
		error = 0;

		if (res != NULL) {
			sbuf_cat(sb, res);
			free(res);
		}
		free(var);
		var = NULL;
	}

	free(var);
	sbuf_finish(sb);
	res = (error == 0) ? strdup(sbuf_data(sb)) : NULL;
	sbuf_delete(sb);
	if (res == NULL)
		errno = ENOMEM;
	return (res);
}
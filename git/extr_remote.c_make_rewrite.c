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
struct rewrites {int rewrite_nr; struct rewrite** rewrite; int /*<<< orphan*/  rewrite_alloc; } ;
struct rewrite {int baselen; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct rewrite**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,int) ; 
 struct rewrite* xcalloc (int,int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 
 int /*<<< orphan*/  xstrndup (char const*,int) ; 

__attribute__((used)) static struct rewrite *make_rewrite(struct rewrites *r, const char *base, int len)
{
	struct rewrite *ret;
	int i;

	for (i = 0; i < r->rewrite_nr; i++) {
		if (len
		    ? (len == r->rewrite[i]->baselen &&
		       !strncmp(base, r->rewrite[i]->base, len))
		    : !strcmp(base, r->rewrite[i]->base))
			return r->rewrite[i];
	}

	ALLOC_GROW(r->rewrite, r->rewrite_nr + 1, r->rewrite_alloc);
	ret = xcalloc(1, sizeof(struct rewrite));
	r->rewrite[r->rewrite_nr++] = ret;
	if (len) {
		ret->base = xstrndup(base, len);
		ret->baselen = len;
	}
	else {
		ret->base = xstrdup(base);
		ret->baselen = strlen(base);
	}
	return ret;
}
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
struct _sm {double m; int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int /*<<< orphan*/  ED (char*,char const*) ; 
 int /*<<< orphan*/  ND (char*,...) ; 
 scalar_t__ strchr (int /*<<< orphan*/ ,char) ; 
 double strtod (char const*,char**) ; 

__attribute__((used)) static double
parse_gen(const char *arg, const struct _sm *conv, int *err)
{
	double d;
	char *ep;
	int dummy;

	if (err == NULL)
		err = &dummy;
	*err = 0;
	if (arg == NULL)
		goto error;
	d = strtod(arg, &ep);
	if (ep == arg) { /* no value */
		ED("bad argument %s", arg);
		goto error;
	}
	/* special case, no conversion */
	if (conv == NULL && *ep == '\0')
		goto done;
	ND("checking %s [%s]", arg, ep);
	for (;conv->s; conv++) {
		if (strchr(conv->s, *ep))
			goto done;
	}
error:
	*err = 1;	/* unrecognised */
	return 0;

done:
	if (conv) {
		ND("scale is %s %lf", conv->s, conv->m);
		d *= conv->m; /* apply default conversion */
	}
	ND("returning %lf", d);
	return d;
}
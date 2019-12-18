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
typedef  int int32_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int FEEDEQ_GAIN_DIV ; 
 int FEEDEQ_IF2PREAMP (int,int) ; 
 int FEEDEQ_PREAMP_FMAX ; 
 int FEEDEQ_PREAMP_FMIN ; 
 int FEEDEQ_PREAMP_IMAX ; 
 int FEEDEQ_PREAMP_IMIN ; 
 int FEEDEQ_PREAMP_INVALID ; 
 int FEEDEQ_PREAMP_SIGNMARK (int) ; 
 int abs (int) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,...) ; 
 int sscanf (char const*,char*,int*,int*) ; 
 scalar_t__ strcasecmp (char const*,char const*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int32_t
feed_eq_scan_preamp_arg(const char *s)
{
	int r, i, f;
	size_t len;
	char buf[32];

	bzero(buf, sizeof(buf));

	/* XXX kind of ugly, but works for now.. */

	r = sscanf(s, "%d.%d", &i, &f);

	if (r == 1 && !(i < FEEDEQ_PREAMP_IMIN || i > FEEDEQ_PREAMP_IMAX)) {
		snprintf(buf, sizeof(buf), "%c%d",
		    FEEDEQ_PREAMP_SIGNMARK(i), abs(i));
		f = 0;
	} else if (r == 2 &&
	    !(i < FEEDEQ_PREAMP_IMIN || i > FEEDEQ_PREAMP_IMAX ||
	    f < FEEDEQ_PREAMP_FMIN || f > FEEDEQ_PREAMP_FMAX))
		snprintf(buf, sizeof(buf), "%c%d.%d",
		    FEEDEQ_PREAMP_SIGNMARK(i), abs(i), f);
	else
		return (FEEDEQ_PREAMP_INVALID);

	len = strlen(s);
	if (len > 2 && strcasecmp(s + len - 2, "dB") == 0)
		strlcat(buf, "dB", sizeof(buf));

	if (i == 0 && *s == '-')
		*buf = '-';

	if (strcasecmp(buf + ((*s >= '0' && *s <= '9') ? 1 : 0), s) != 0)
		return (FEEDEQ_PREAMP_INVALID);

	while ((f / FEEDEQ_GAIN_DIV) > 0)
		f /= FEEDEQ_GAIN_DIV;

	return (((i < 0 || *buf == '-') ? -1 : 1) * FEEDEQ_IF2PREAMP(i, f));
}
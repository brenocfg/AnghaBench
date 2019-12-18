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
typedef  int u_int ;
struct tok {char const* s; int v; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 size_t strlcpy (char*,char const*,size_t) ; 

__attribute__((used)) static char *
bittok2str_internal(register const struct tok *lp, register const char *fmt,
	   register u_int v, const char *sep)
{
        static char buf[1024+1]; /* our string buffer */
        char *bufp = buf;
        size_t space_left = sizeof(buf), string_size;
        register u_int rotbit; /* this is the bit we rotate through all bitpositions */
        register u_int tokval;
        const char * sepstr = "";

	while (lp != NULL && lp->s != NULL) {
            tokval=lp->v;   /* load our first value */
            rotbit=1;
            while (rotbit != 0) {
                /*
                 * lets AND the rotating bit with our token value
                 * and see if we have got a match
                 */
		if (tokval == (v&rotbit)) {
                    /* ok we have found something */
                    if (space_left <= 1)
                        return (buf); /* only enough room left for NUL, if that */
                    string_size = strlcpy(bufp, sepstr, space_left);
                    if (string_size >= space_left)
                        return (buf);    /* we ran out of room */
                    bufp += string_size;
                    space_left -= string_size;
                    if (space_left <= 1)
                        return (buf); /* only enough room left for NUL, if that */
                    string_size = strlcpy(bufp, lp->s, space_left);
                    if (string_size >= space_left)
                        return (buf);    /* we ran out of room */
                    bufp += string_size;
                    space_left -= string_size;
                    sepstr = sep;
                    break;
                }
                rotbit=rotbit<<1; /* no match - lets shift and try again */
            }
            lp++;
	}

        if (bufp == buf)
            /* bummer - lets print the "unknown" message as advised in the fmt string if we got one */
            (void)snprintf(buf, sizeof(buf), fmt == NULL ? "#%08x" : fmt, v);
        return (buf);
}
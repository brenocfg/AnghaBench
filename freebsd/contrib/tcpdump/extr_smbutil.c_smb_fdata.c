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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  s ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 size_t PTR_DIFF (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * smb_fdata1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  smb_print_data (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

const u_char *
smb_fdata(netdissect_options *ndo,
          const u_char *buf, const char *fmt, const u_char *maxbuf,
          int unicodestr)
{
    static int depth = 0;
    char s[128];
    char *p;

    while (*fmt) {
	switch (*fmt) {
	case '*':
	    fmt++;
	    while (buf < maxbuf) {
		const u_char *buf2;
		depth++;
		buf2 = smb_fdata(ndo, buf, fmt, maxbuf, unicodestr);
		depth--;
		if (buf2 == NULL)
		    return(NULL);
		if (buf2 == buf)
		    return(buf);
		buf = buf2;
	    }
	    return(buf);

	case '|':
	    fmt++;
	    if (buf >= maxbuf)
		return(buf);
	    break;

	case '%':
	    fmt++;
	    buf = maxbuf;
	    break;

	case '#':
	    fmt++;
	    return(buf);
	    break;

	case '[':
	    fmt++;
	    if (buf >= maxbuf)
		return(buf);
	    memset(s, 0, sizeof(s));
	    p = strchr(fmt, ']');
	    if ((size_t)(p - fmt + 1) > sizeof(s)) {
		/* overrun */
		return(buf);
	    }
	    strncpy(s, fmt, p - fmt);
	    s[p - fmt] = '\0';
	    fmt = p + 1;
	    buf = smb_fdata1(ndo, buf, s, maxbuf, unicodestr);
	    if (buf == NULL)
		return(NULL);
	    break;

	default:
	    ND_PRINT((ndo, "%c", *fmt));
	    fmt++;
	    break;
	}
    }
    if (!depth && buf < maxbuf) {
	size_t len = PTR_DIFF(maxbuf, buf);
	ND_PRINT((ndo, "Data: (%lu bytes)\n", (unsigned long)len));
	smb_print_data(ndo, buf, len);
	return(buf + len);
    }
    return(buf);
}
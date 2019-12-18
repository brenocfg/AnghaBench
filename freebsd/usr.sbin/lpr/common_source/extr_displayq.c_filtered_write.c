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
typedef  int /*<<< orphan*/  destbuf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isprintch (char) ; 

__attribute__((used)) static void
filtered_write(char *wbuffer, int wlen, FILE *wstream)
{
	static char lastchar, savedchar;
	char *chkptr, *dest_end, *dest_ch, *nxtptr, *w_end;
	int destlen;
	char destbuf[BUFSIZ];

	if (wbuffer == NULL) {
		if (savedchar != '\0') {
			if (savedchar == '\r')
				savedchar = '\n';
			fputc(savedchar, wstream);
			lastchar = savedchar;
			savedchar = '\0';
		}
		if (lastchar != '\0' && lastchar != '\n')
			fputc('\n', wstream);
		lastchar = '\0';
		return;
	}

	dest_ch = &destbuf[0];
	dest_end = dest_ch + sizeof(destbuf);
	chkptr = wbuffer;
	w_end = wbuffer + wlen;
	lastchar = '\0';
	if (savedchar != '\0') {
		chkptr = &savedchar;
		nxtptr = wbuffer;
	} else
		nxtptr = chkptr + 1;

	while (chkptr < w_end) {
		if (nxtptr < w_end) {
			if ((*chkptr == '\r' && *nxtptr == '\n') ||
			    (*chkptr == '\n' && *nxtptr == '\r')) {
				*dest_ch++ = '\n';
				/* want to skip past that second character */
				nxtptr++;
				goto check_next;
			}
		} else {
			/* This is the last byte in the buffer given on this
			 * call, so check if it could be the first-byte of a
			 * significant two-byte sequence.  If it is, then
			 * don't write it out now, but save for checking in
			 * the next call.
			 */
			savedchar = '\0';
			if (*chkptr == '\r' || *chkptr == '\n') {
				savedchar = *chkptr;
				break;
			}
		}
		if (*chkptr == '\r')
			*dest_ch++ = '\n';
#if 0		/* XXX - don't translate unprintable characters (yet) */
		else if (*chkptr != '\t' && *chkptr != '\n' &&
		    !isprintch(*chkptr))
			*dest_ch++ = '?';
#endif
		else
			*dest_ch++ = *chkptr;

check_next:
		chkptr = nxtptr;
		nxtptr = chkptr + 1;
		if (dest_ch >= dest_end) {
			destlen = dest_ch - &destbuf[0];
			fwrite(destbuf, 1, destlen, wstream);
			lastchar = destbuf[destlen - 1];
			dest_ch = &destbuf[0];
		}
	}
	destlen = dest_ch - &destbuf[0];
	if (destlen > 0) {
		fwrite(destbuf, 1, destlen, wstream);
		lastchar = destbuf[destlen - 1];
	}
}
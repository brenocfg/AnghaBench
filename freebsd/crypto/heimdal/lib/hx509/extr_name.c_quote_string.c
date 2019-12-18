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
 unsigned char Q_RFC2253_HEX ; 
 unsigned char Q_RFC2253_QUOTE ; 
 unsigned char Q_RFC2253_QUOTE_FIRST ; 
 unsigned char Q_RFC2253_QUOTE_LAST ; 
 int /*<<< orphan*/  assert (int) ; 
 int* char_map ; 
 unsigned char* malloc (size_t) ; 
 int snprintf (char*,size_t,char*,unsigned char) ; 

__attribute__((used)) static char *
quote_string(const char *f, size_t len, int flags, size_t *rlen)
{
    size_t i, j, tolen;
    const unsigned char *from = (const unsigned char *)f;
    unsigned char *to;

    tolen = len * 3 + 1;
    to = malloc(tolen);
    if (to == NULL)
	return NULL;

    for (i = 0, j = 0; i < len; i++) {
	unsigned char map = char_map[from[i]] & flags;
	if (i == 0 && (map & Q_RFC2253_QUOTE_FIRST)) {
	    to[j++] = '\\';
	    to[j++] = from[i];
	} else if ((i + 1) == len && (map & Q_RFC2253_QUOTE_LAST)) {

	    to[j++] = '\\';
	    to[j++] = from[i];
	} else if (map & Q_RFC2253_QUOTE) {
	    to[j++] = '\\';
	    to[j++] = from[i];
	} else if (map & Q_RFC2253_HEX) {
	    int l = snprintf((char *)&to[j], tolen - j - 1,
			     "#%02x", (unsigned char)from[i]);
	    j += l;
	} else {
	    to[j++] = from[i];
	}
    }
    to[j] = '\0';
    assert(j < tolen);
    *rlen = j;
    return (char *)to;
}
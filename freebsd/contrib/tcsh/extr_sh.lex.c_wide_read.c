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
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  cbuf ;
typedef  unsigned char Char ;

/* Variables and functions */
 int /*<<< orphan*/  BUFSIZE ; 
 unsigned char INVALID_BYTE ; 
 int /*<<< orphan*/  L_INCR ; 
 size_t MB_LEN_MAX ; 
 int /*<<< orphan*/  USE (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 int* fclens ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int normal_mbtowc (unsigned char*,char*,size_t) ; 
 int /*<<< orphan*/  reset_mbtowc () ; 
 size_t xread (int,char*,size_t) ; 

ssize_t
wide_read(int fildes, Char *buf, size_t nchars, int use_fclens)
{
    char cbuf[BUFSIZE + 1];
    ssize_t res, r = 0;
    size_t partial;
    int err;

    if (nchars == 0)
	return 0;
    assert (nchars <= sizeof(cbuf) / sizeof(*cbuf));
    USE(use_fclens);
    res = 0;
    partial = 0;
    do {
	size_t i;
	size_t len = nchars > partial ? nchars - partial : 1;

	if (partial + len >= sizeof(cbuf) / sizeof(*cbuf))
	    break;
	
	r = xread(fildes, cbuf + partial, len);
		  
	if (partial == 0 && r <= 0)
	    break;
	partial += r;
	i = 0;
	while (i < partial && nchars != 0) {
	    int tlen;

	    tlen = normal_mbtowc(buf + res, cbuf + i, partial - i);
	    if (tlen == -1) {
	        reset_mbtowc();
		if ((partial - i) < MB_LEN_MAX && r > 0)
		    /* Maybe a partial character and there is still a chance
		       to read more */
		    break;
		buf[res] = (unsigned char)cbuf[i] | INVALID_BYTE;
	    }
	    if (tlen <= 0)
		tlen = 1;
#ifdef WIDE_STRINGS
	    if (use_fclens)
		fclens[res] = tlen;
#endif
	    i += tlen;
	    res++;
	    nchars--;
	}
	if (i != partial)
	    memmove(cbuf, cbuf + i, partial - i);
	partial -= i;
    } while (partial != 0 && nchars > 0);
    /* Throwing away possible partial multibyte characters on error if the
       stream is not seekable */
    err = errno;
    lseek(fildes, -(off_t)partial, L_INCR);
    errno = err;
    return res != 0 ? res : r;
}
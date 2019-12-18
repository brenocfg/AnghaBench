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
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int read (int,char*,int) ; 

int
fgetstr(char *buf, int size, int fd)
{
    char	c;
    int		err, len;
    
    size--;	/* leave space for terminator */
    len = 0;
    while (size != 0) {
	err = read(fd, &c, sizeof(c));
	if (err < 0)		/* read error */
	    return(-1);
	if (err == 0) {		/* EOF */
	    if (len == 0)
		return(-1);	/* nothing to read */
	    break;
	}
	if ((c == '\r') ||	/* line terminators */
	    (c == '\n'))
	    break;
	*buf++ = c;		/* keep char */
	size--;
	len++;
    }
    *buf = 0;
    return(len);
}
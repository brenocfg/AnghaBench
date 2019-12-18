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
 int LS_DIRS ; 
 int LS_DISP_COLUMN ; 
 int LS_DISP_CROSS ; 
 int LS_DISP_LONG ; 
 int LS_DISP_MODE ; 
 int LS_IGNORE_DOT ; 
 int LS_INODE ; 
 int LS_RECURSIVE ; 
 int LS_SHOW_ALL ; 
 int LS_SIZE ; 
 int LS_SORT_MODE ; 
 int LS_SORT_MTIME ; 
 int LS_SORT_NAME ; 
 int LS_SORT_REVERSE ; 
 int LS_SORT_SIZE ; 
 int LS_TYPE ; 

__attribute__((used)) static int
parse_flags(const char *options)
{
#ifdef TEST
    int flags = LS_SORT_NAME | LS_IGNORE_DOT | LS_DISP_COLUMN;
#else
    int flags = LS_SORT_NAME | LS_IGNORE_DOT | LS_DISP_LONG;
#endif

    const char *p;
    if(options == NULL || *options != '-')
	return flags;
    for(p = options + 1; *p; p++) {
	switch(*p) {
	case '1':
	    flags = (flags & ~LS_DISP_MODE);
	    break;
	case 'a':
	    flags |= LS_SHOW_ALL;
	    /*FALLTHROUGH*/
	case 'A':
	    flags &= ~LS_IGNORE_DOT;
	    break;
	case 'C':
	    flags = (flags & ~LS_DISP_MODE) | LS_DISP_COLUMN;
	    break;
	case 'd':
	    flags |= LS_DIRS;
	    break;
	case 'f':
	    flags = (flags & ~LS_SORT_MODE);
	    break;
	case 'F':
	    flags |= LS_TYPE;
	    break;
	case 'i':
	    flags |= LS_INODE;
	    break;
	case 'l':
	    flags = (flags & ~LS_DISP_MODE) | LS_DISP_LONG;
	    break;
	case 'r':
	    flags |= LS_SORT_REVERSE;
	    break;
	case 'R':
	    flags |= LS_RECURSIVE;
	    break;
	case 's':
	    flags |= LS_SIZE;
	    break;
	case 'S':
	    flags = (flags & ~LS_SORT_MODE) | LS_SORT_SIZE;
	    break;
	case 't':
	    flags = (flags & ~LS_SORT_MODE) | LS_SORT_MTIME;
	    break;
	case 'x':
	    flags = (flags & ~LS_DISP_MODE) | LS_DISP_CROSS;
	    break;
	    /* these are a bunch of unimplemented flags from BSD ls */
	case 'k': /* display sizes in kB */
	case 'c': /* last change time */
	case 'L': /* list symlink target */
	case 'm': /* stream output */
	case 'o': /* BSD file flags */
	case 'p': /* display / after directories */
	case 'q': /* print non-graphic characters */
	case 'u': /* use last access time */
	case 'T': /* display complete time */
	case 'W': /* include whiteouts */
	    break;
	}
    }
    return flags;
}
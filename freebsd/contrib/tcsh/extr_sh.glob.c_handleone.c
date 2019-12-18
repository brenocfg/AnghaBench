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
typedef  char Char ;

/* Variables and functions */
 int ERR_AMBIG ; 
 int ERR_NAME ; 
#define  G_APPEND 130 
#define  G_ERROR 129 
#define  G_IGNORE 128 
 size_t Strlen (char*) ; 
 char* Strsave (int /*<<< orphan*/ ) ; 
 int TRIM ; 
 int /*<<< orphan*/  blkfree (char**) ; 
 int /*<<< orphan*/  setname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  short2str (char*) ; 
 int /*<<< orphan*/  stderror (int) ; 
 int /*<<< orphan*/  strip (char*) ; 
 char* xmalloc (size_t) ; 

__attribute__((used)) static Char *
handleone(Char *str, Char **vl, int action)
{
    size_t chars;
    Char **t, *p, *strp;

    switch (action) {
    case G_ERROR:
	setname(short2str(str));
	blkfree(vl);
	stderror(ERR_NAME | ERR_AMBIG);
	break;
    case G_APPEND:
	chars = 0;
	for (t = vl; (p = *t++) != NULL; chars++)
	    chars += Strlen(p);
	str = xmalloc(chars * sizeof(Char));
	for (t = vl, strp = str; (p = *t++) != NULL; chars++) {
	    while (*p)
		 *strp++ = *p++ & TRIM;
	    *strp++ = ' ';
	}
	*--strp = '\0';
	blkfree(vl);
	break;
    case G_IGNORE:
	str = Strsave(strip(*vl));
	blkfree(vl);
	break;
    default:
	break;
    }
    return (str);
}
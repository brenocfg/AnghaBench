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
struct tildecache {char const* user; char* home; int /*<<< orphan*/  hlen; } ;
typedef  char Char ;

/* Variables and functions */
 int Strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  Strlen (char*) ; 
 char const* Strsave (char const*) ; 
 int TILINCR ; 
 char* gethomedir (char const*) ; 
 int /*<<< orphan*/  qsort (struct tildecache*,int,int,int /*<<< orphan*/ ) ; 
 struct tildecache* tcache ; 
 int /*<<< orphan*/  tildecompare ; 
 int tlength ; 
 int tsize ; 
 struct tildecache* xmalloc (int) ; 
 struct tildecache* xrealloc (struct tildecache*,int) ; 

Char   *
gettilde(const Char *us)
{
    struct tildecache *bp1, *bp2, *bp;
    Char *hd;

    /* Ignore NIS special names */
    if (*us == '+' || *us == '-')
	return NULL;

    if (tcache == NULL)
	tcache = xmalloc(TILINCR * sizeof(struct tildecache));
    /*
     * Binary search
     */
    for (bp1 = tcache, bp2 = tcache + tlength; bp1 < bp2;) {
	int i;

	bp = bp1 + ((bp2 - bp1) >> 1);
	if ((i = *us - *bp->user) == 0 && (i = Strcmp(us, bp->user)) == 0)
	    return (bp->home);
	if (i < 0)
	    bp2 = bp;
	else
	    bp1 = bp + 1;
    }
    /*
     * Not in the cache, try to get it from the passwd file
     */
    hd = gethomedir(us);
    if (hd == NULL)
	return NULL;

    /*
     * Update the cache
     */
    tcache[tlength].user = Strsave(us);
    tcache[tlength].home = hd;
    tcache[tlength++].hlen = Strlen(hd);

    qsort(tcache, tlength, sizeof(struct tildecache), tildecompare);

    if (tlength == tsize) {
	tsize += TILINCR;
	tcache = xrealloc(tcache, tsize * sizeof(struct tildecache));
    }
    return (hd);
}
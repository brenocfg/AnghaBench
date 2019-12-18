#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int16_t ;
struct TYPE_11__ {char* page; int addr; } ;
struct TYPE_10__ {int BSIZE; char* tmp_key; } ;
typedef  TYPE_1__ HTAB ;
typedef  int /*<<< orphan*/  DBT ;
typedef  TYPE_2__ BUFHEAD ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int FULL_KEY ; 
 int FULL_KEY_DATA ; 
 scalar_t__ __big_return (TYPE_1__*,TYPE_2__*,int,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* __get_buf (TYPE_1__*,int,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 

__attribute__((used)) static int
collect_key(HTAB *hashp, BUFHEAD *bufp, int len, DBT *val, int set)
{
	BUFHEAD *xbp;
	char *p;
	int mylen, totlen;
	u_int16_t *bp, save_addr;

	p = bufp->page;
	bp = (u_int16_t *)p;
	mylen = hashp->BSIZE - bp[1];

	save_addr = bufp->addr;
	totlen = len + mylen;
	if (bp[2] == FULL_KEY || bp[2] == FULL_KEY_DATA) {    /* End of Key. */
		if (hashp->tmp_key != NULL)
			free(hashp->tmp_key);
		if ((hashp->tmp_key = (char *)malloc(totlen)) == NULL)
			return (-1);
		if (__big_return(hashp, bufp, 1, val, set))
			return (-1);
	} else {
		xbp = __get_buf(hashp, bp[bp[0] - 1], bufp, 0);
		if (!xbp || ((totlen =
		    collect_key(hashp, xbp, totlen, val, set)) < 1))
			return (-1);
	}
	if (bufp->addr != save_addr) {
		errno = EINVAL;		/* MIS -- OUT OF BUFFERS */
		return (-1);
	}
	memmove(&hashp->tmp_key[len], (bufp->page) + bp[1], mylen);
	return (totlen);
}
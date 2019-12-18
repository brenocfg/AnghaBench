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
struct message {int m_lines; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int LINESIZE ; 
 int gethfield (int /*<<< orphan*/ *,char*,int,char**) ; 
 char* ishfield (char*,char*,char const*) ; 
 scalar_t__ readline (int /*<<< orphan*/ *,char*,int) ; 
 char* save2str (char*,char*) ; 
 int /*<<< orphan*/ * setinput (struct message*) ; 

char *
hfield(const char *field, struct message *mp)
{
	FILE *ibuf;
	char linebuf[LINESIZE];
	int lc;
	char *hfield;
	char *colon, *oldhfield = NULL;

	ibuf = setinput(mp);
	if ((lc = mp->m_lines - 1) < 0)
		return (NULL);
	if (readline(ibuf, linebuf, LINESIZE) < 0)
		return (NULL);
	while (lc > 0) {
		if ((lc = gethfield(ibuf, linebuf, lc, &colon)) < 0)
			return (oldhfield);
		if ((hfield = ishfield(linebuf, colon, field)) != NULL)
			oldhfield = save2str(hfield, oldhfield);
	}
	return (oldhfield);
}
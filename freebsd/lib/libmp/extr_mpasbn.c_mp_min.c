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
typedef  int /*<<< orphan*/  MINT ;

/* Variables and functions */
 int /*<<< orphan*/  MPERR (char*) ; 
 int /*<<< orphan*/ * _dtom (char*,char*) ; 
 int /*<<< orphan*/  _mfree (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _movem (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* fgetln (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  stdin ; 

void
mp_min(MINT *mp)
{
	MINT *rmp;
	char *line, *nline;
	size_t linelen;

	line = fgetln(stdin, &linelen);
	if (line == NULL)
		MPERR(("min"));
	nline = malloc(linelen + 1);
	if (nline == NULL)
		MPERR(("min"));
	memcpy(nline, line, linelen);
	nline[linelen] = '\0';
	rmp = _dtom("min", nline);
	_movem("min", rmp, mp);
	_mfree("min", rmp);
	free(nline);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rerr {scalar_t__ code; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  re_endp; } ;
typedef  TYPE_1__ regex_t ;

/* Variables and functions */
 struct rerr* rerrs ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
regatoi(const regex_t *preg, char *localbuf)
{
#if 0 /* we don't seem to use this and it gives a warning. */
	struct rerr *r;
	size_t siz;
	char *p;

	for (r = rerrs; r->code != 0; r++)
		if (strcmp(r->name, preg->re_endp) == 0)
			break;
	if (r->code == 0)
		return("0");

	sprintf(localbuf, "%d", r->code);
#else
	*localbuf = '\0';
#endif
	return(localbuf);
}
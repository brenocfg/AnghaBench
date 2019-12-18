#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
struct TYPE_4__ {scalar_t__ fieldno; scalar_t__ filenum; } ;
typedef  int /*<<< orphan*/  OLIST ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 TYPE_1__* olist ; 
 int olistalloc ; 
 int olistcnt ; 
 TYPE_1__* realloc (TYPE_1__*,int) ; 
 char* strsep (char**,char*) ; 
 scalar_t__ strtol (char*,char**,int) ; 

__attribute__((used)) static void
fieldarg(char *option)
{
	u_long fieldno, filenum;
	char *end, *token;

	while ((token = strsep(&option, ", \t")) != NULL) {
		if (*token == '\0')
			continue;
		if (token[0] == '0')
			filenum = fieldno = 0;
		else if ((token[0] == '1' || token[0] == '2') &&
		    token[1] == '.') {
			filenum = token[0] - '0';
			fieldno = strtol(token + 2, &end, 10);
			if (*end)
				errx(1, "malformed -o option field");
			if (fieldno == 0)
				errx(1, "field numbers are 1 based");
			--fieldno;
		} else
			errx(1, "malformed -o option field");
		if (olistcnt == olistalloc) {
			olistalloc += 50;
			if ((olist = realloc(olist,
			    olistalloc * sizeof(OLIST))) == NULL)
				err(1, NULL);
		}
		olist[olistcnt].filenum = filenum;
		olist[olistcnt].fieldno = fieldno;
		++olistcnt;
	}
}
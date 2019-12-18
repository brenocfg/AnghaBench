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
struct TYPE_3__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ token_t ;

/* Variables and functions */
 char* strchr (char*,char) ; 
 char* strdup (int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 
 scalar_t__ strncasecmp (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static char *
selectFrom(char *str, token_t *list)
{
     char	*sep, *sp;
     token_t	*lp;
     int	n;

     sp = str;
     do {
	  sep = strchr(sp, ',');
	  if(sep != NULL)
	       n = sep - sp;
	  else
	       n = strlen(sp);
	  
	  for(lp = list; lp->name != NULL; lp++) {
	       if(strncasecmp(lp->name, sp, n) == 0)
		    return strdup(lp->name);
	  }
	  sp = sep + 1;
     } while(sep != NULL);

     return NULL;
}
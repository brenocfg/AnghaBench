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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (int,int) ; 
 char* get_line (int /*<<< orphan*/ *) ; 
 scalar_t__ isspace (unsigned char) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
getConfig(FILE *fd, char *key, char **Ar, int *nargs)
{
     char	*lp, *p, **ar;
     int	state, len, n;

     ar = Ar;
     if(key)
	  len = strlen(key);
     else
	  len = 0;
     state = 0;
     while((lp = get_line(fd)) != NULL) {
	  for(; isspace((unsigned char)*lp); lp++)
	       ;
	  switch(state) {
	  case 0:
	       if((p = strchr(lp, '{')) != NULL) {
		    while((--p > lp) && *p && isspace((unsigned char)*p));
		    n = p - lp;
		    if(len && strncmp(lp, key, MAX(n, len)) == 0)
			 state = 2;
		    else
			 state = 1;
		    continue;
	       }
	       break;

	  case 1:
	       if(*lp == '}')
		    state = 0;
	       continue;

	  case 2:
	       if(*lp == '}')
		    goto done;
	       
	       break;
	  }

	  
	  for(p = &lp[strlen(lp)-1]; isspace((unsigned char)*p); p--)
	       *p = 0;
	  if((*nargs)-- > 0)
	       *ar++ = strdup(lp);
     }

 done:
     if(*nargs > 0)
	  *ar = 0;
     *nargs =  ar - Ar;
     return ar - Ar;
}
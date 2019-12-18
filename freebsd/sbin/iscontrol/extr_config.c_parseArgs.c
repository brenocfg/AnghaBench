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
struct TYPE_3__ {int /*<<< orphan*/  tokenID; } ;
typedef  TYPE_1__ textkey_t ;
typedef  int /*<<< orphan*/  isc_opt_t ;

/* Variables and functions */
 scalar_t__ isspace (unsigned char) ; 
 TYPE_1__* keyLookup (char*) ; 
 int /*<<< orphan*/  setOption (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 char* strchr (char*,char) ; 

void
parseArgs(int nargs, char **args, isc_opt_t *op)
{
     char	**ar;
     char	*p, *v;
     textkey_t	*tk;

     for(ar = args; nargs > 0; nargs--, ar++) {
	  p = strchr(*ar, '=');
	  if(p == NULL)
	       continue;
	  *p = 0;
	  v = p + 1;
	  while(isspace((unsigned char)*--p))
	       *p = 0;
	  while(isspace((unsigned char)*v))
	       v++;
	  if((tk = keyLookup(*ar)) == NULL)
	       continue;
	  setOption(op, tk->tokenID, v);
     }
}
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

/* Variables and functions */
 int /*<<< orphan*/  M_ISC ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  bcopy (char*,char*,size_t) ; 
 scalar_t__ copyinstr (char*,char*,size_t,size_t*) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
i_strdupin(char *s, size_t maxlen)
{
     size_t	len;
     char	*p, *q;

     p = malloc(maxlen, M_ISC, M_WAITOK);
     if(copyinstr(s, p, maxlen, &len)) {
	  free(p, M_ISC);
	  return NULL;
     }
     q = malloc(len, M_ISC, M_WAITOK);
     bcopy(p, q, len);
     free(p, M_ISC);

     return q;
}
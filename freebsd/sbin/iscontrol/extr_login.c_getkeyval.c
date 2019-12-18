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
struct TYPE_3__ {int ds_len; scalar_t__ ds_addr; } ;
typedef  TYPE_1__ pdu_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug_called (int) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static char *
getkeyval(char *key, pdu_t *pp)
{
    char	*ptr;
    int	klen, len, n;

    debug_called(3);

    len = pp->ds_len;
    ptr = (char *)pp->ds_addr;
    klen = strlen(key);
    while(len > klen) {
	 if(strncmp(key, ptr, klen) == 0)
	      return ptr+klen;
	 n = strlen(ptr) + 1;
	 len -= n;
	 ptr += n;
    }
    return 0;
}
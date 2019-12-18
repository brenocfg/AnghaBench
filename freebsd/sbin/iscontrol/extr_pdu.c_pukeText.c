#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int opcode; } ;
struct TYPE_6__ {TYPE_1__ bhs; } ;
struct TYPE_7__ {size_t ds_len; TYPE_2__ ipdu; scalar_t__ ds_addr; } ;
typedef  TYPE_3__ pdu_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
pukeText(char *it, pdu_t *pp)
{
     char	*ptr;
     int	cmd;
     size_t	len, n;

     len = pp->ds_len;
     ptr = (char *)pp->ds_addr;
     cmd = pp->ipdu.bhs.opcode;

     printf("%s: cmd=0x%x len=%d\n", it, cmd, (int)len);
     while(len > 0) {
	  printf("\t%s\n", ptr);
	  n = strlen(ptr) + 1;
	  len -= n;
	  ptr += n;
     }
}
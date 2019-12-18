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
typedef  scalar_t__ u_char ;
struct TYPE_3__ {int ds_len; scalar_t__* ds_addr; } ;
typedef  TYPE_1__ pdu_t ;
typedef  int /*<<< orphan*/  isess_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
handledDiscoveryResp(isess_t *sess, pdu_t *pp)
{
     u_char	*ptr;
     int	len, n;

     debug_called(3);

     len = pp->ds_len;
     ptr = pp->ds_addr;
     while(len > 0) {
	  if(*ptr != 0)
	       printf("%s\n", ptr);
	  n = strlen((char *)ptr) + 1;
	  len -= n;
	  ptr += n;
     }
     return 0;
}
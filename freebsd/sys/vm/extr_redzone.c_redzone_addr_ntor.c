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
typedef  void* caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  redzone_get_size (void*) ; 
 void* redzone_roundup (int /*<<< orphan*/ ) ; 

void *
redzone_addr_ntor(caddr_t naddr)
{

	return (naddr - redzone_roundup(redzone_get_size(naddr)));
}
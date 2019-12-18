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
struct ip_fw_chain {int /*<<< orphan*/  srvstate; int /*<<< orphan*/  srvmap; } ;

/* Variables and functions */
 int IPFW_OBJECTS_DEFAULT ; 
 int /*<<< orphan*/  M_IPFW ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  ipfw_objhash_create (int) ; 
 int /*<<< orphan*/  malloc (int,int /*<<< orphan*/ ,int) ; 

void
ipfw_init_srv(struct ip_fw_chain *ch)
{

	ch->srvmap = ipfw_objhash_create(IPFW_OBJECTS_DEFAULT);
	ch->srvstate = malloc(sizeof(void *) * IPFW_OBJECTS_DEFAULT,
	    M_IPFW, M_WAITOK | M_ZERO);
}
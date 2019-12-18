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
typedef  int /*<<< orphan*/  uint8_t ;
struct table_info {int /*<<< orphan*/  lookup; void* state; } ;
struct ip_fw_chain {int dummy; } ;
struct iftable_cfg {int size; void* main_ptr; struct ip_fw_chain* ch; int /*<<< orphan*/  ii; } ;
struct ifidx {int dummy; } ;

/* Variables and functions */
 int DEFAULT_IFIDX_SIZE ; 
 int /*<<< orphan*/  M_IPFW ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  ipfw_objhash_create (int) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ta_lookup_ifidx ; 

__attribute__((used)) static int
ta_init_ifidx(struct ip_fw_chain *ch, void **ta_state, struct table_info *ti,
    char *data, uint8_t tflags)
{
	struct iftable_cfg *icfg;

	icfg = malloc(sizeof(struct iftable_cfg), M_IPFW, M_WAITOK | M_ZERO);

	icfg->ii = ipfw_objhash_create(DEFAULT_IFIDX_SIZE);
	icfg->size = DEFAULT_IFIDX_SIZE;
	icfg->main_ptr = malloc(sizeof(struct ifidx) * icfg->size, M_IPFW,
	    M_WAITOK | M_ZERO);
	icfg->ch = ch;

	*ta_state = icfg;
	ti->state = icfg->main_ptr;
	ti->lookup = ta_lookup_ifidx;

	return (0);
}
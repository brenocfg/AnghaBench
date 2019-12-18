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
struct numarray_cfg {int size; void* main_ptr; } ;
struct numarray {int dummy; } ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IPFW ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ta_lookup_numarray ; 

__attribute__((used)) static int
ta_init_numarray(struct ip_fw_chain *ch, void **ta_state, struct table_info *ti,
    char *data, uint8_t tflags)
{
	struct numarray_cfg *cfg;

	cfg = malloc(sizeof(*cfg), M_IPFW, M_WAITOK | M_ZERO);

	cfg->size = 16;
	cfg->main_ptr = malloc(sizeof(struct numarray) * cfg->size, M_IPFW,
	    M_WAITOK | M_ZERO);

	*ta_state = cfg;
	ti->state = cfg->main_ptr;
	ti->lookup = ta_lookup_numarray;

	return (0);
}
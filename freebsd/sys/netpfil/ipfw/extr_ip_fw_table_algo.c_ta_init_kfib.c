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
struct table_info {int data; int /*<<< orphan*/  lookup; } ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 int E2BIG ; 
 int kfib_parse_opts (int*,char*) ; 
 int rt_numfibs ; 
 int /*<<< orphan*/  ta_lookup_kfib ; 

__attribute__((used)) static int
ta_init_kfib(struct ip_fw_chain *ch, void **ta_state, struct table_info *ti,
    char *data, uint8_t tflags)
{
	int error, fibnum;

	fibnum = 0;
	if ((error = kfib_parse_opts(&fibnum, data)) != 0)
		return (error);

	if (fibnum >= rt_numfibs)
		return (E2BIG);

	ti->data = fibnum;
	ti->lookup = ta_lookup_kfib;

	return (0);
}
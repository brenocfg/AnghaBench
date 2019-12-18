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
struct TYPE_3__ {unsigned int data2; int /*<<< orphan*/  data1; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ pmi_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMI_TYPE_FREQ_CHANGE ; 
 int /*<<< orphan*/  cbe_cpu_to_node (int) ; 
 long jiffies ; 
 long jiffies_to_msecs (long) ; 
 int /*<<< orphan*/  pmi_send_message (TYPE_1__) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

int cbe_cpufreq_set_pmode_pmi(int cpu, unsigned int pmode)
{
	int ret;
	pmi_message_t pmi_msg;
#ifdef DEBUG
	long time;
#endif
	pmi_msg.type = PMI_TYPE_FREQ_CHANGE;
	pmi_msg.data1 =	cbe_cpu_to_node(cpu);
	pmi_msg.data2 = pmode;

#ifdef DEBUG
	time = jiffies;
#endif
	pmi_send_message(pmi_msg);

#ifdef DEBUG
	time = jiffies  - time;
	time = jiffies_to_msecs(time);
	pr_debug("had to wait %lu ms for a transition using " \
		 "PMI\n", time);
#endif
	ret = pmi_msg.data2;
	pr_debug("PMI returned slow mode %d\n", ret);

	return ret;
}
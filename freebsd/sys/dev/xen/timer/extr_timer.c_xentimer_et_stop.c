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
struct xentimer_pcpu_data {scalar_t__ timer; } ;
struct eventtimer {int dummy; } ;

/* Variables and functions */
 struct xentimer_pcpu_data* DPCPU_PTR (int /*<<< orphan*/ ) ; 
 int PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_id ; 
 int /*<<< orphan*/  xentimer_pcpu ; 
 int xentimer_vcpu_stop_timer (int) ; 

__attribute__((used)) static int
xentimer_et_stop(struct eventtimer *et)
{
	int cpu = PCPU_GET(vcpu_id);
	struct xentimer_pcpu_data *pcpu = DPCPU_PTR(xentimer_pcpu);

	pcpu->timer = 0;
	return (xentimer_vcpu_stop_timer(cpu));
}
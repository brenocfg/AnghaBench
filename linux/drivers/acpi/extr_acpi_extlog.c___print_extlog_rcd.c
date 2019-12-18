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
struct acpi_hest_generic_status {scalar_t__ error_severity; } ;
typedef  int /*<<< orphan*/  pfx_seq ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 scalar_t__ CPER_SEV_CORRECTED ; 
 char* KERN_ERR ; 
 char* KERN_INFO ; 
 unsigned int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cper_estatus_print (char*,struct acpi_hest_generic_status*) ; 
 int /*<<< orphan*/  printk (char*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,unsigned int) ; 

__attribute__((used)) static void __print_extlog_rcd(const char *pfx,
			       struct acpi_hest_generic_status *estatus, int cpu)
{
	static atomic_t seqno;
	unsigned int curr_seqno;
	char pfx_seq[64];

	if (!pfx) {
		if (estatus->error_severity <= CPER_SEV_CORRECTED)
			pfx = KERN_INFO;
		else
			pfx = KERN_ERR;
	}
	curr_seqno = atomic_inc_return(&seqno);
	snprintf(pfx_seq, sizeof(pfx_seq), "%s{%u}", pfx, curr_seqno);
	printk("%s""Hardware error detected on CPU%d\n", pfx_seq, cpu);
	cper_estatus_print(pfx_seq, estatus);
}
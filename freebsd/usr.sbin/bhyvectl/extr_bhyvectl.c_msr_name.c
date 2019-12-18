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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  MSR_CSTAR 140 
#define  MSR_EFER 139 
#define  MSR_FSBASE 138 
#define  MSR_GSBASE 137 
#define  MSR_KGSBASE 136 
#define  MSR_LSTAR 135 
#define  MSR_PAT 134 
#define  MSR_SF_MASK 133 
#define  MSR_STAR 132 
#define  MSR_SYSENTER_CS_MSR 131 
#define  MSR_SYSENTER_EIP_MSR 130 
#define  MSR_SYSENTER_ESP_MSR 129 
#define  MSR_TSC 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static const char *
msr_name(uint32_t msr)
{
	static char buf[32];

	switch(msr) {
	case MSR_TSC:
		return ("MSR_TSC");
	case MSR_EFER:
		return ("MSR_EFER");
	case MSR_STAR:
		return ("MSR_STAR");
	case MSR_LSTAR:	
		return ("MSR_LSTAR");
	case MSR_CSTAR:
		return ("MSR_CSTAR");
	case MSR_SF_MASK:
		return ("MSR_SF_MASK");
	case MSR_FSBASE:
		return ("MSR_FSBASE");
	case MSR_GSBASE:
		return ("MSR_GSBASE");
	case MSR_KGSBASE:
		return ("MSR_KGSBASE");
	case MSR_SYSENTER_CS_MSR:
		return ("MSR_SYSENTER_CS_MSR");
	case MSR_SYSENTER_ESP_MSR:
		return ("MSR_SYSENTER_ESP_MSR");
	case MSR_SYSENTER_EIP_MSR:
		return ("MSR_SYSENTER_EIP_MSR");
	case MSR_PAT:
		return ("MSR_PAT");
	}
	snprintf(buf, sizeof(buf), "MSR       %#08x", msr);

	return (buf);
}
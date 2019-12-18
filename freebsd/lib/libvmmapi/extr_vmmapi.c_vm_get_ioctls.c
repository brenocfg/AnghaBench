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
typedef  int /*<<< orphan*/  vm_ioctl_cmds ;
typedef  int /*<<< orphan*/  const cap_ioctl_t ;

/* Variables and functions */
#define  VM_ACTIVATE_CPU 181 
#define  VM_ALLOC_MEMSEG 180 
#define  VM_BIND_PPTDEV 179 
#define  VM_GET_CAPABILITY 178 
#define  VM_GET_CPUS 177 
#define  VM_GET_GPA_PMAP 176 
#define  VM_GET_HPET_CAPABILITIES 175 
#define  VM_GET_INTINFO 174 
#define  VM_GET_MEMSEG 173 
#define  VM_GET_REGISTER 172 
#define  VM_GET_REGISTER_SET 171 
#define  VM_GET_SEGMENT_DESCRIPTOR 170 
#define  VM_GET_TOPOLOGY 169 
#define  VM_GET_X2APIC_STATE 168 
#define  VM_GLA2GPA 167 
#define  VM_GLA2GPA_NOFAULT 166 
#define  VM_INJECT_EXCEPTION 165 
#define  VM_INJECT_NMI 164 
#define  VM_IOAPIC_ASSERT_IRQ 163 
#define  VM_IOAPIC_DEASSERT_IRQ 162 
#define  VM_IOAPIC_PINCOUNT 161 
#define  VM_IOAPIC_PULSE_IRQ 160 
#define  VM_ISA_ASSERT_IRQ 159 
#define  VM_ISA_DEASSERT_IRQ 158 
#define  VM_ISA_PULSE_IRQ 157 
#define  VM_ISA_SET_IRQ_TRIGGER 156 
#define  VM_LAPIC_IRQ 155 
#define  VM_LAPIC_LOCAL_IRQ 154 
#define  VM_LAPIC_MSI 153 
#define  VM_MAP_PPTDEV_MMIO 152 
#define  VM_MMAP_GETNEXT 151 
#define  VM_MMAP_MEMSEG 150 
#define  VM_PPTDEV_MSI 149 
#define  VM_PPTDEV_MSIX 148 
#define  VM_REINIT 147 
#define  VM_RESTART_INSTRUCTION 146 
#define  VM_RESUME_CPU 145 
#define  VM_RTC_GETTIME 144 
#define  VM_RTC_READ 143 
#define  VM_RTC_SETTIME 142 
#define  VM_RTC_WRITE 141 
#define  VM_RUN 140 
#define  VM_SET_CAPABILITY 139 
#define  VM_SET_INTINFO 138 
#define  VM_SET_REGISTER 137 
#define  VM_SET_REGISTER_SET 136 
#define  VM_SET_SEGMENT_DESCRIPTOR 135 
#define  VM_SET_TOPOLOGY 134 
#define  VM_SET_X2APIC_STATE 133 
#define  VM_STATS 132 
#define  VM_STAT_DESC 131 
#define  VM_SUSPEND 130 
#define  VM_SUSPEND_CPU 129 
#define  VM_UNBIND_PPTDEV 128 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  const* malloc (int) ; 
 size_t nitems (int /*<<< orphan*/  const*) ; 

const cap_ioctl_t *
vm_get_ioctls(size_t *len)
{
	cap_ioctl_t *cmds;
	/* keep in sync with machine/vmm_dev.h */
	static const cap_ioctl_t vm_ioctl_cmds[] = { VM_RUN, VM_SUSPEND, VM_REINIT,
	    VM_ALLOC_MEMSEG, VM_GET_MEMSEG, VM_MMAP_MEMSEG, VM_MMAP_MEMSEG,
	    VM_MMAP_GETNEXT, VM_SET_REGISTER, VM_GET_REGISTER,
	    VM_SET_SEGMENT_DESCRIPTOR, VM_GET_SEGMENT_DESCRIPTOR,
	    VM_SET_REGISTER_SET, VM_GET_REGISTER_SET,
	    VM_INJECT_EXCEPTION, VM_LAPIC_IRQ, VM_LAPIC_LOCAL_IRQ,
	    VM_LAPIC_MSI, VM_IOAPIC_ASSERT_IRQ, VM_IOAPIC_DEASSERT_IRQ,
	    VM_IOAPIC_PULSE_IRQ, VM_IOAPIC_PINCOUNT, VM_ISA_ASSERT_IRQ,
	    VM_ISA_DEASSERT_IRQ, VM_ISA_PULSE_IRQ, VM_ISA_SET_IRQ_TRIGGER,
	    VM_SET_CAPABILITY, VM_GET_CAPABILITY, VM_BIND_PPTDEV,
	    VM_UNBIND_PPTDEV, VM_MAP_PPTDEV_MMIO, VM_PPTDEV_MSI,
	    VM_PPTDEV_MSIX, VM_INJECT_NMI, VM_STATS, VM_STAT_DESC,
	    VM_SET_X2APIC_STATE, VM_GET_X2APIC_STATE,
	    VM_GET_HPET_CAPABILITIES, VM_GET_GPA_PMAP, VM_GLA2GPA,
	    VM_GLA2GPA_NOFAULT,
	    VM_ACTIVATE_CPU, VM_GET_CPUS, VM_SUSPEND_CPU, VM_RESUME_CPU,
	    VM_SET_INTINFO, VM_GET_INTINFO,
	    VM_RTC_WRITE, VM_RTC_READ, VM_RTC_SETTIME, VM_RTC_GETTIME,
	    VM_RESTART_INSTRUCTION, VM_SET_TOPOLOGY, VM_GET_TOPOLOGY };

	if (len == NULL) {
		cmds = malloc(sizeof(vm_ioctl_cmds));
		if (cmds == NULL)
			return (NULL);
		bcopy(vm_ioctl_cmds, cmds, sizeof(vm_ioctl_cmds));
		return (cmds);
	}

	*len = nitems(vm_ioctl_cmds);
	return (NULL);
}
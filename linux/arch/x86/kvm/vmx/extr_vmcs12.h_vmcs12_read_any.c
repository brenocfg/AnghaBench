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
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct vmcs12 {int dummy; } ;
typedef  int natural_width ;

/* Variables and functions */
#define  VMCS_FIELD_WIDTH_NATURAL_WIDTH 131 
#define  VMCS_FIELD_WIDTH_U16 130 
#define  VMCS_FIELD_WIDTH_U32 129 
#define  VMCS_FIELD_WIDTH_U64 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int vmcs_field_width (unsigned long) ; 

__attribute__((used)) static inline u64 vmcs12_read_any(struct vmcs12 *vmcs12, unsigned long field,
				  u16 offset)
{
	char *p = (char *)vmcs12 + offset;

	switch (vmcs_field_width(field)) {
	case VMCS_FIELD_WIDTH_NATURAL_WIDTH:
		return *((natural_width *)p);
	case VMCS_FIELD_WIDTH_U16:
		return *((u16 *)p);
	case VMCS_FIELD_WIDTH_U32:
		return *((u32 *)p);
	case VMCS_FIELD_WIDTH_U64:
		return *((u64 *)p);
	default:
		WARN_ON_ONCE(1);
		return -1;
	}
}
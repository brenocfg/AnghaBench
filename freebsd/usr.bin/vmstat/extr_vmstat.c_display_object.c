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
typedef  char const* uintmax_t ;
struct kinfo_vmobject {char const* kvo_ref_count; char const* kvo_shadow_count; int kvo_memattr; int kvo_type; char const* kvo_path; scalar_t__ kvo_inactive; scalar_t__ kvo_active; scalar_t__ kvo_resident; } ;

/* Variables and functions */
#define  KVME_TYPE_DEAD 148 
#define  KVME_TYPE_DEFAULT 147 
#define  KVME_TYPE_DEVICE 146 
#define  KVME_TYPE_MGTDEVICE 145 
#define  KVME_TYPE_NONE 144 
#define  KVME_TYPE_PHYS 143 
#define  KVME_TYPE_SG 142 
#define  KVME_TYPE_SWAP 141 
#define  KVME_TYPE_UNKNOWN 140 
#define  KVME_TYPE_VNODE 139 
#define  VM_MEMATTR_CACHEABLE 138 
#define  VM_MEMATTR_DEVICE 137 
#define  VM_MEMATTR_NOCACHE 136 
#define  VM_MEMATTR_PREFETCHABLE 135 
#define  VM_MEMATTR_UNCACHEABLE 134 
#define  VM_MEMATTR_WB_WA 133 
#define  VM_MEMATTR_WEAK_UNCACHEABLE 132 
#define  VM_MEMATTR_WRITE_BACK 131 
#define  VM_MEMATTR_WRITE_COMBINING 130 
#define  VM_MEMATTR_WRITE_PROTECTED 129 
#define  VM_MEMATTR_WRITE_THROUGH 128 
 int /*<<< orphan*/  xo_close_instance (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,char const*) ; 
 int /*<<< orphan*/  xo_open_instance (char*) ; 

__attribute__((used)) static void
display_object(struct kinfo_vmobject *kvo)
{
	const char *str;

	xo_open_instance("object");
	xo_emit("{:resident/%5ju} ", (uintmax_t)kvo->kvo_resident);
	xo_emit("{:active/%5ju} ", (uintmax_t)kvo->kvo_active);
	xo_emit("{:inactive/%5ju} ", (uintmax_t)kvo->kvo_inactive);
	xo_emit("{:refcount/%3d} ", kvo->kvo_ref_count);
	xo_emit("{:shadowcount/%3d} ", kvo->kvo_shadow_count);
	switch (kvo->kvo_memattr) {
#ifdef VM_MEMATTR_UNCACHEABLE
	case VM_MEMATTR_UNCACHEABLE:
		str = "UC";
		break;
#endif
#ifdef VM_MEMATTR_WRITE_COMBINING
	case VM_MEMATTR_WRITE_COMBINING:
		str = "WC";
		break;
#endif
#ifdef VM_MEMATTR_WRITE_THROUGH
	case VM_MEMATTR_WRITE_THROUGH:
		str = "WT";
		break;
#endif
#ifdef VM_MEMATTR_WRITE_PROTECTED
	case VM_MEMATTR_WRITE_PROTECTED:
		str = "WP";
		break;
#endif
#ifdef VM_MEMATTR_WRITE_BACK
	case VM_MEMATTR_WRITE_BACK:
		str = "WB";
		break;
#endif
#ifdef VM_MEMATTR_WEAK_UNCACHEABLE
	case VM_MEMATTR_WEAK_UNCACHEABLE:
		str = "UC-";
		break;
#endif
#ifdef VM_MEMATTR_WB_WA
	case VM_MEMATTR_WB_WA:
		str = "WB";
		break;
#endif
#ifdef VM_MEMATTR_NOCACHE
	case VM_MEMATTR_NOCACHE:
		str = "NC";
		break;
#endif
#ifdef VM_MEMATTR_DEVICE
	case VM_MEMATTR_DEVICE:
		str = "DEV";
		break;
#endif
#ifdef VM_MEMATTR_CACHEABLE
	case VM_MEMATTR_CACHEABLE:
		str = "C";
		break;
#endif
#ifdef VM_MEMATTR_PREFETCHABLE
	case VM_MEMATTR_PREFETCHABLE:
		str = "PRE";
		break;
#endif
	default:
		str = "??";
		break;
	}
	xo_emit("{:attribute/%-3s} ", str);
	switch (kvo->kvo_type) {
	case KVME_TYPE_NONE:
		str = "--";
		break;
	case KVME_TYPE_DEFAULT:
		str = "df";
		break;
	case KVME_TYPE_VNODE:
		str = "vn";
		break;
	case KVME_TYPE_SWAP:
		str = "sw";
		break;
	case KVME_TYPE_DEVICE:
		str = "dv";
		break;
	case KVME_TYPE_PHYS:
		str = "ph";
		break;
	case KVME_TYPE_DEAD:
		str = "dd";
		break;
	case KVME_TYPE_SG:
		str = "sg";
		break;
	case KVME_TYPE_MGTDEVICE:
		str = "md";
		break;
	case KVME_TYPE_UNKNOWN:
	default:
		str = "??";
		break;
	}
	xo_emit("{:type/%-2s} ", str);
	xo_emit("{:path/%-s}\n", kvo->kvo_path);
	xo_close_instance("object");
}
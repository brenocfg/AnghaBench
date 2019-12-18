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
struct procstat {int dummy; } ;
struct kinfo_vmentry {int kve_protection; char const* kve_resident; char const* kve_private_resident; char const* kve_ref_count; char const* kve_shadow_count; int kve_flags; int kve_type; char const* kve_path; scalar_t__ kve_end; scalar_t__ kve_start; } ;
struct kinfo_proc {char const* ki_pid; } ;

/* Variables and functions */
 int KVME_FLAG_COW ; 
 int KVME_FLAG_GROWS_DOWN ; 
 int KVME_FLAG_GROWS_UP ; 
 int KVME_FLAG_NEEDS_COPY ; 
 int KVME_FLAG_SUPER ; 
 int KVME_FLAG_USER_WIRED ; 
 int KVME_PROT_EXEC ; 
 int KVME_PROT_READ ; 
 int KVME_PROT_WRITE ; 
#define  KVME_TYPE_DEAD 137 
#define  KVME_TYPE_DEFAULT 136 
#define  KVME_TYPE_DEVICE 135 
#define  KVME_TYPE_MGTDEVICE 134 
#define  KVME_TYPE_NONE 133 
#define  KVME_TYPE_PHYS 132 
#define  KVME_TYPE_SG 131 
#define  KVME_TYPE_SWAP 130 
#define  KVME_TYPE_UNKNOWN 129 
#define  KVME_TYPE_VNODE 128 
 int PS_OPT_NOHEADER ; 
 int /*<<< orphan*/  free (struct kinfo_vmentry*) ; 
 struct kinfo_vmentry* procstat_getvmmap (struct procstat*,struct kinfo_proc*,int*) ; 
 int procstat_opts ; 
 int /*<<< orphan*/  xo_close_container (char*) ; 
 int /*<<< orphan*/  xo_close_instance (char*) ; 
 int /*<<< orphan*/  xo_close_list (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,...) ; 
 int /*<<< orphan*/  xo_open_container (char*) ; 
 int /*<<< orphan*/  xo_open_instance (char*) ; 
 int /*<<< orphan*/  xo_open_list (char*) ; 

void
procstat_vm(struct procstat *procstat, struct kinfo_proc *kipp)
{
	struct kinfo_vmentry *freep, *kve;
	int ptrwidth;
	int i, cnt;
	const char *str, *lstr;

	ptrwidth = 2*sizeof(void *) + 2;
	if ((procstat_opts & PS_OPT_NOHEADER) == 0)
		xo_emit("{T:/%5s %*s %*s %3s %4s %4s %3s %3s %-5s %-2s %-s}\n",
		    "PID", ptrwidth, "START", ptrwidth, "END", "PRT", "RES",
		    "PRES", "REF", "SHD", "FLAG", "TP", "PATH");

	xo_emit("{ek:process_id/%d}", kipp->ki_pid);

	freep = procstat_getvmmap(procstat, kipp, &cnt);
	if (freep == NULL)
		return;
	xo_open_list("vm");
	for (i = 0; i < cnt; i++) {
		xo_open_instance("vm");
		kve = &freep[i];
		xo_emit("{dk:process_id/%5d} ", kipp->ki_pid);
		xo_emit("{d:kve_start/%#*jx} ", ptrwidth,
		    (uintmax_t)kve->kve_start);
		xo_emit("{d:kve_end/%#*jx} ", ptrwidth,
		    (uintmax_t)kve->kve_end);
		xo_emit("{e:kve_start/%#jx}", (uintmax_t)kve->kve_start);
		xo_emit("{e:kve_end/%#jx}", (uintmax_t)kve->kve_end);
		xo_emit("{d:read/%s}", kve->kve_protection & KVME_PROT_READ ?
		    "r" : "-");
		xo_emit("{d:write/%s}", kve->kve_protection & KVME_PROT_WRITE ?
		    "w" : "-");
		xo_emit("{d:exec/%s} ", kve->kve_protection & KVME_PROT_EXEC ?
		    "x" : "-");
		xo_open_container("kve_protection");
		xo_emit("{en:read/%s}", kve->kve_protection & KVME_PROT_READ ?
		    "true" : "false");
		xo_emit("{en:write/%s}", kve->kve_protection & KVME_PROT_WRITE ?
		    "true" : "false");
		xo_emit("{en:exec/%s}", kve->kve_protection & KVME_PROT_EXEC ?
		    "true" : "false");
		xo_close_container("kve_protection");
		xo_emit("{:kve_resident/%4d/%d} ", kve->kve_resident);
		xo_emit("{:kve_private_resident/%4d/%d} ",
		    kve->kve_private_resident);
		xo_emit("{:kve_ref_count/%3d/%d} ", kve->kve_ref_count);
		xo_emit("{:kve_shadow_count/%3d/%d} ", kve->kve_shadow_count);
		xo_emit("{d:copy_on_write/%-1s}", kve->kve_flags &
		    KVME_FLAG_COW ? "C" : "-");
		xo_emit("{d:need_copy/%-1s}", kve->kve_flags &
		    KVME_FLAG_NEEDS_COPY ? "N" : "-");
		xo_emit("{d:super_pages/%-1s}", kve->kve_flags &
		    KVME_FLAG_SUPER ? "S" : "-");
		xo_emit("{d:grows_down/%-1s}", kve->kve_flags &
		    KVME_FLAG_GROWS_UP ? "U" : kve->kve_flags &
		    KVME_FLAG_GROWS_DOWN ? "D" : "-");
		xo_emit("{d:wired/%-1s} ", kve->kve_flags &
		    KVME_FLAG_USER_WIRED ? "W" : "-");
		xo_open_container("kve_flags");
		xo_emit("{en:copy_on_write/%s}", kve->kve_flags &
		    KVME_FLAG_COW ? "true" : "false");
		xo_emit("{en:needs_copy/%s}", kve->kve_flags &
		    KVME_FLAG_NEEDS_COPY ? "true" : "false");
		xo_emit("{en:super_pages/%s}", kve->kve_flags &
		    KVME_FLAG_SUPER ? "true" : "false");
		xo_emit("{en:grows_up/%s}", kve->kve_flags &
		    KVME_FLAG_GROWS_UP ? "true" : "false");
		xo_emit("{en:grows_down/%s}", kve->kve_flags &
		    KVME_FLAG_GROWS_DOWN ? "true" : "false");
		xo_emit("{en:wired/%s}", kve->kve_flags &
		    KVME_FLAG_USER_WIRED ? "true" : "false");
		xo_close_container("kve_flags");
		switch (kve->kve_type) {
		case KVME_TYPE_NONE:
			str = "--";
			lstr = "none";
			break;
		case KVME_TYPE_DEFAULT:
			str = "df";
			lstr = "default";
			break;
		case KVME_TYPE_VNODE:
			str = "vn";
			lstr = "vnode";
			break;
		case KVME_TYPE_SWAP:
			str = "sw";
			lstr = "swap";
			break;
		case KVME_TYPE_DEVICE:
			str = "dv";
			lstr = "device";
			break;
		case KVME_TYPE_PHYS:
			str = "ph";
			lstr = "physical";
			break;
		case KVME_TYPE_DEAD:
			str = "dd";
			lstr = "dead";
			break;
		case KVME_TYPE_SG:
			str = "sg";
			lstr = "scatter/gather";
			break;
		case KVME_TYPE_MGTDEVICE:
			str = "md";
			lstr = "managed_device";
			break;
		case KVME_TYPE_UNKNOWN:
		default:
			str = "??";
			lstr = "unknown";
			break;
		}
		xo_emit("{d:kve_type/%-2s} ", str);
		xo_emit("{e:kve_type/%s}", lstr);
		xo_emit("{:kve_path/%-s/%s}\n", kve->kve_path);
		xo_close_instance("vm");
	}
	xo_close_list("vm");
	free(freep);
}
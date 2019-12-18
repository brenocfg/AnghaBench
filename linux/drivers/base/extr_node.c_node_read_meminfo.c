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
struct sysinfo {int totalram; int freeram; int totalhigh; int freehigh; int sharedram; } ;
struct pglist_data {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int id; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int HPAGE_PMD_NR ; 
 int K (int) ; 
 struct pglist_data* NODE_DATA (int) ; 
 int /*<<< orphan*/  NR_ACTIVE_ANON ; 
 int /*<<< orphan*/  NR_ACTIVE_FILE ; 
 int /*<<< orphan*/  NR_ANON_MAPPED ; 
 int /*<<< orphan*/  NR_ANON_THPS ; 
 int /*<<< orphan*/  NR_BOUNCE ; 
 int /*<<< orphan*/  NR_FILE_DIRTY ; 
 int /*<<< orphan*/  NR_FILE_MAPPED ; 
 int /*<<< orphan*/  NR_FILE_PAGES ; 
 int /*<<< orphan*/  NR_FILE_PMDMAPPED ; 
 int /*<<< orphan*/  NR_FILE_THPS ; 
 int /*<<< orphan*/  NR_INACTIVE_ANON ; 
 int /*<<< orphan*/  NR_INACTIVE_FILE ; 
 int /*<<< orphan*/  NR_KERNEL_MISC_RECLAIMABLE ; 
 int /*<<< orphan*/  NR_KERNEL_STACK_KB ; 
 int /*<<< orphan*/  NR_MLOCK ; 
 int /*<<< orphan*/  NR_PAGETABLE ; 
 int /*<<< orphan*/  NR_SHMEM_PMDMAPPED ; 
 int /*<<< orphan*/  NR_SHMEM_THPS ; 
 int /*<<< orphan*/  NR_SLAB_RECLAIMABLE ; 
 int /*<<< orphan*/  NR_SLAB_UNRECLAIMABLE ; 
 int /*<<< orphan*/  NR_UNEVICTABLE ; 
 int /*<<< orphan*/  NR_UNSTABLE_NFS ; 
 int /*<<< orphan*/  NR_WRITEBACK ; 
 int /*<<< orphan*/  NR_WRITEBACK_TEMP ; 
 scalar_t__ hugetlb_report_node_meminfo (int,char*) ; 
 int node_page_state (struct pglist_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  si_meminfo_node (struct sysinfo*,int) ; 
 int sprintf (char*,char*,int,int,int,int,int,int,int,int,...) ; 
 int sum_zone_node_page_state (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t node_read_meminfo(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	int n;
	int nid = dev->id;
	struct pglist_data *pgdat = NODE_DATA(nid);
	struct sysinfo i;
	unsigned long sreclaimable, sunreclaimable;

	si_meminfo_node(&i, nid);
	sreclaimable = node_page_state(pgdat, NR_SLAB_RECLAIMABLE);
	sunreclaimable = node_page_state(pgdat, NR_SLAB_UNRECLAIMABLE);
	n = sprintf(buf,
		       "Node %d MemTotal:       %8lu kB\n"
		       "Node %d MemFree:        %8lu kB\n"
		       "Node %d MemUsed:        %8lu kB\n"
		       "Node %d Active:         %8lu kB\n"
		       "Node %d Inactive:       %8lu kB\n"
		       "Node %d Active(anon):   %8lu kB\n"
		       "Node %d Inactive(anon): %8lu kB\n"
		       "Node %d Active(file):   %8lu kB\n"
		       "Node %d Inactive(file): %8lu kB\n"
		       "Node %d Unevictable:    %8lu kB\n"
		       "Node %d Mlocked:        %8lu kB\n",
		       nid, K(i.totalram),
		       nid, K(i.freeram),
		       nid, K(i.totalram - i.freeram),
		       nid, K(node_page_state(pgdat, NR_ACTIVE_ANON) +
				node_page_state(pgdat, NR_ACTIVE_FILE)),
		       nid, K(node_page_state(pgdat, NR_INACTIVE_ANON) +
				node_page_state(pgdat, NR_INACTIVE_FILE)),
		       nid, K(node_page_state(pgdat, NR_ACTIVE_ANON)),
		       nid, K(node_page_state(pgdat, NR_INACTIVE_ANON)),
		       nid, K(node_page_state(pgdat, NR_ACTIVE_FILE)),
		       nid, K(node_page_state(pgdat, NR_INACTIVE_FILE)),
		       nid, K(node_page_state(pgdat, NR_UNEVICTABLE)),
		       nid, K(sum_zone_node_page_state(nid, NR_MLOCK)));

#ifdef CONFIG_HIGHMEM
	n += sprintf(buf + n,
		       "Node %d HighTotal:      %8lu kB\n"
		       "Node %d HighFree:       %8lu kB\n"
		       "Node %d LowTotal:       %8lu kB\n"
		       "Node %d LowFree:        %8lu kB\n",
		       nid, K(i.totalhigh),
		       nid, K(i.freehigh),
		       nid, K(i.totalram - i.totalhigh),
		       nid, K(i.freeram - i.freehigh));
#endif
	n += sprintf(buf + n,
		       "Node %d Dirty:          %8lu kB\n"
		       "Node %d Writeback:      %8lu kB\n"
		       "Node %d FilePages:      %8lu kB\n"
		       "Node %d Mapped:         %8lu kB\n"
		       "Node %d AnonPages:      %8lu kB\n"
		       "Node %d Shmem:          %8lu kB\n"
		       "Node %d KernelStack:    %8lu kB\n"
		       "Node %d PageTables:     %8lu kB\n"
		       "Node %d NFS_Unstable:   %8lu kB\n"
		       "Node %d Bounce:         %8lu kB\n"
		       "Node %d WritebackTmp:   %8lu kB\n"
		       "Node %d KReclaimable:   %8lu kB\n"
		       "Node %d Slab:           %8lu kB\n"
		       "Node %d SReclaimable:   %8lu kB\n"
		       "Node %d SUnreclaim:     %8lu kB\n"
#ifdef CONFIG_TRANSPARENT_HUGEPAGE
		       "Node %d AnonHugePages:  %8lu kB\n"
		       "Node %d ShmemHugePages: %8lu kB\n"
		       "Node %d ShmemPmdMapped: %8lu kB\n"
		       "Node %d FileHugePages: %8lu kB\n"
		       "Node %d FilePmdMapped: %8lu kB\n"
#endif
			,
		       nid, K(node_page_state(pgdat, NR_FILE_DIRTY)),
		       nid, K(node_page_state(pgdat, NR_WRITEBACK)),
		       nid, K(node_page_state(pgdat, NR_FILE_PAGES)),
		       nid, K(node_page_state(pgdat, NR_FILE_MAPPED)),
		       nid, K(node_page_state(pgdat, NR_ANON_MAPPED)),
		       nid, K(i.sharedram),
		       nid, sum_zone_node_page_state(nid, NR_KERNEL_STACK_KB),
		       nid, K(sum_zone_node_page_state(nid, NR_PAGETABLE)),
		       nid, K(node_page_state(pgdat, NR_UNSTABLE_NFS)),
		       nid, K(sum_zone_node_page_state(nid, NR_BOUNCE)),
		       nid, K(node_page_state(pgdat, NR_WRITEBACK_TEMP)),
		       nid, K(sreclaimable +
			      node_page_state(pgdat, NR_KERNEL_MISC_RECLAIMABLE)),
		       nid, K(sreclaimable + sunreclaimable),
		       nid, K(sreclaimable),
		       nid, K(sunreclaimable)
#ifdef CONFIG_TRANSPARENT_HUGEPAGE
		       ,
		       nid, K(node_page_state(pgdat, NR_ANON_THPS) *
				       HPAGE_PMD_NR),
		       nid, K(node_page_state(pgdat, NR_SHMEM_THPS) *
				       HPAGE_PMD_NR),
		       nid, K(node_page_state(pgdat, NR_SHMEM_PMDMAPPED) *
				       HPAGE_PMD_NR),
		       nid, K(node_page_state(pgdat, NR_FILE_THPS) *
				       HPAGE_PMD_NR),
		       nid, K(node_page_state(pgdat, NR_FILE_PMDMAPPED) *
				       HPAGE_PMD_NR)
#endif
		       );
	n += hugetlb_report_node_meminfo(nid, buf + n);
	return n;
}
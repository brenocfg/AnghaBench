#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct kvm_sev_info {unsigned long pages_locked; } ;
struct kvm {int dummy; } ;
struct TYPE_2__ {struct kvm_sev_info sev_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_IPC_LOCK ; 
 int /*<<< orphan*/  FOLL_WRITE ; 
 int GFP_KERNEL_ACCOUNT ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int __GFP_ZERO ; 
 struct page** __vmalloc (unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 unsigned long get_user_pages_fast (unsigned long,unsigned long,int /*<<< orphan*/ ,struct page**) ; 
 struct page** kmalloc (unsigned long,int) ; 
 int /*<<< orphan*/  kvfree (struct page**) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long,...) ; 
 int /*<<< orphan*/  release_pages (struct page**,unsigned long) ; 
 unsigned long rlimit (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_kvm_svm (struct kvm*) ; 

__attribute__((used)) static struct page **sev_pin_memory(struct kvm *kvm, unsigned long uaddr,
				    unsigned long ulen, unsigned long *n,
				    int write)
{
	struct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	unsigned long npages, npinned, size;
	unsigned long locked, lock_limit;
	struct page **pages;
	unsigned long first, last;

	if (ulen == 0 || uaddr + ulen < uaddr)
		return NULL;

	/* Calculate number of pages. */
	first = (uaddr & PAGE_MASK) >> PAGE_SHIFT;
	last = ((uaddr + ulen - 1) & PAGE_MASK) >> PAGE_SHIFT;
	npages = (last - first + 1);

	locked = sev->pages_locked + npages;
	lock_limit = rlimit(RLIMIT_MEMLOCK) >> PAGE_SHIFT;
	if (locked > lock_limit && !capable(CAP_IPC_LOCK)) {
		pr_err("SEV: %lu locked pages exceed the lock limit of %lu.\n", locked, lock_limit);
		return NULL;
	}

	/* Avoid using vmalloc for smaller buffers. */
	size = npages * sizeof(struct page *);
	if (size > PAGE_SIZE)
		pages = __vmalloc(size, GFP_KERNEL_ACCOUNT | __GFP_ZERO,
				  PAGE_KERNEL);
	else
		pages = kmalloc(size, GFP_KERNEL_ACCOUNT);

	if (!pages)
		return NULL;

	/* Pin the user virtual address. */
	npinned = get_user_pages_fast(uaddr, npages, FOLL_WRITE, pages);
	if (npinned != npages) {
		pr_err("SEV: Failure locking %lu pages.\n", npages);
		goto err;
	}

	*n = npages;
	sev->pages_locked = locked;

	return pages;

err:
	if (npinned > 0)
		release_pages(pages, npinned);

	kvfree(pages);
	return NULL;
}
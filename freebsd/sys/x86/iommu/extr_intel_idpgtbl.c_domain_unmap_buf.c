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
struct dmar_domain {int dummy; } ;
typedef  int /*<<< orphan*/  dmar_gaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_DOMAIN_PGLOCK (struct dmar_domain*) ; 
 int /*<<< orphan*/  DMAR_DOMAIN_PGUNLOCK (struct dmar_domain*) ; 
 int domain_unmap_buf_locked (struct dmar_domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
domain_unmap_buf(struct dmar_domain *domain, dmar_gaddr_t base,
    dmar_gaddr_t size, int flags)
{
	int error;

	DMAR_DOMAIN_PGLOCK(domain);
	error = domain_unmap_buf_locked(domain, base, size, flags);
	DMAR_DOMAIN_PGUNLOCK(domain);
	return (error);
}
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
struct irq_domain {int /*<<< orphan*/  parent; } ;
struct fwnode_handle {int dummy; } ;
typedef  int /*<<< orphan*/  DEFINE_MUTEX ;

/* Variables and functions */
 struct fwnode_handle* irq_domain_alloc_named_fwnode (char*) ; 
 struct irq_domain* irq_domain_create_tree (struct fwnode_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_domain_free_fwnode (struct fwnode_handle*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_domain_ops ; 
 int /*<<< orphan*/  x86_vector_domain ; 

__attribute__((used)) static struct irq_domain *uv_get_irq_domain(void)
{
	static struct irq_domain *uv_domain;
	static DEFINE_MUTEX(uv_lock);
	struct fwnode_handle *fn;

	mutex_lock(&uv_lock);
	if (uv_domain)
		goto out;

	fn = irq_domain_alloc_named_fwnode("UV-CORE");
	if (!fn)
		goto out;

	uv_domain = irq_domain_create_tree(fn, &uv_domain_ops, NULL);
	irq_domain_free_fwnode(fn);
	if (uv_domain)
		uv_domain->parent = x86_vector_domain;
out:
	mutex_unlock(&uv_lock);

	return uv_domain;
}
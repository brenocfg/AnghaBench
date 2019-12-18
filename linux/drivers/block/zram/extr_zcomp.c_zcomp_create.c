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
struct zcomp {char const* name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct zcomp* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct zcomp*) ; 
 struct zcomp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zcomp_available_algorithm (char const*) ; 
 int zcomp_init (struct zcomp*) ; 

struct zcomp *zcomp_create(const char *compress)
{
	struct zcomp *comp;
	int error;

	if (!zcomp_available_algorithm(compress))
		return ERR_PTR(-EINVAL);

	comp = kzalloc(sizeof(struct zcomp), GFP_KERNEL);
	if (!comp)
		return ERR_PTR(-ENOMEM);

	comp->name = compress;
	error = zcomp_init(comp);
	if (error) {
		kfree(comp);
		return ERR_PTR(error);
	}
	return comp;
}
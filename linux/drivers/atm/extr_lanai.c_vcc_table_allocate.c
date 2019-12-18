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
struct lanai_vcc {int dummy; } ;
struct lanai_dev {int num_vci; struct lanai_vcc** vccs; } ;

/* Variables and functions */
 int /*<<< orphan*/  APRINTK (int,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct lanai_vcc** vzalloc (int) ; 

__attribute__((used)) static int vcc_table_allocate(struct lanai_dev *lanai)
{
#ifdef VCCTABLE_GETFREEPAGE
	APRINTK((lanai->num_vci) * sizeof(struct lanai_vcc *) <= PAGE_SIZE,
	    "vcc table > PAGE_SIZE!");
	lanai->vccs = (struct lanai_vcc **) get_zeroed_page(GFP_KERNEL);
	return (lanai->vccs == NULL) ? -ENOMEM : 0;
#else
	int bytes = (lanai->num_vci) * sizeof(struct lanai_vcc *);
	lanai->vccs = vzalloc(bytes);
	if (unlikely(lanai->vccs == NULL))
		return -ENOMEM;
	return 0;
#endif
}
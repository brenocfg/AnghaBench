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
typedef  void* u32 ;
struct sa_open_data {size_t tmp_length; size_t tmp_size; struct ipv4_range* tmp_base; } ;
struct ipv4_range {void* end; void* start; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int __touch_tmp_base (struct sa_open_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ realloc (struct ipv4_range*,int) ; 

__attribute__((used)) static int ipv4_list_add_range(struct sa_open_data *od, u32 start,
		u32 end, gfp_t gfp)
{
	struct ipv4_range *cur;
	int ret;
	
	/* Ignore a new range if it or a larger range already exists */
	//if (salist_check_ipv4(od->table, start, end))
	//	return 0;
	
	if ((ret = __touch_tmp_base(od, gfp)) < 0)
		return ret;
	
	/* Check if the size is efficient. Enlarge it if needed. */
	if (od->tmp_length + 1 >= od->tmp_size) {
		size_t old_size = od->tmp_size;
		struct ipv4_range *old_base = od->tmp_base;
		
		od->tmp_size *= 2;
		od->tmp_base = (struct ipv4_range *)realloc(od->tmp_base,
				sizeof(struct ipv4_range) * od->tmp_size);
		if (!od->tmp_base) {
			od->tmp_size = old_size;
			od->tmp_base = old_base;
			return -ENOMEM;
		}
	}
	
	cur = &od->tmp_base[od->tmp_length++];
	cur->start = start;
	cur->end = end;
	
	return 0;
}
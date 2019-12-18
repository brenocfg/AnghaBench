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
typedef  int /*<<< orphan*/  const listcoll_t ;

/* Variables and functions */
#define  list_coll 148 
#define  list_coll_1 147 
#define  list_coll_10 146 
#define  list_coll_11 145 
#define  list_coll_12 144 
#define  list_coll_13 143 
#define  list_coll_14 142 
#define  list_coll_15 141 
#define  list_coll_16 140 
#define  list_coll_17 139 
#define  list_coll_18 138 
#define  list_coll_19 137 
#define  list_coll_2 136 
#define  list_coll_20 135 
#define  list_coll_3 134 
#define  list_coll_4 133 
#define  list_coll_5 132 
#define  list_coll_6 131 
#define  list_coll_7 130 
#define  list_coll_8 129 
#define  list_coll_9 128 

listcoll_t
get_list_call_func(size_t offset)
{
	static const listcoll_t lsarray[] = { list_coll, list_coll_1,
	    list_coll_2, list_coll_3, list_coll_4, list_coll_5,
	    list_coll_6, list_coll_7, list_coll_8, list_coll_9,
	    list_coll_10, list_coll_11, list_coll_12, list_coll_13,
	    list_coll_14, list_coll_15, list_coll_16, list_coll_17,
	    list_coll_18, list_coll_19, list_coll_20 };

	if (offset <= 20)
		return (lsarray[offset]);

	return (list_coll);
}
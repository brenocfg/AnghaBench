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
typedef  int /*<<< orphan*/  u8 ;
struct sta_info {size_t* supp_op_classes; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (size_t*) ; 
 size_t* os_malloc (int) ; 
 int /*<<< orphan*/  os_memcpy (size_t*,int /*<<< orphan*/  const*,size_t) ; 

void ap_copy_sta_supp_op_classes(struct sta_info *sta,
				 const u8 *supp_op_classes,
				 size_t supp_op_classes_len)
{
	if (!supp_op_classes)
		return;
	os_free(sta->supp_op_classes);
	sta->supp_op_classes = os_malloc(1 + supp_op_classes_len);
	if (!sta->supp_op_classes)
		return;

	sta->supp_op_classes[0] = supp_op_classes_len;
	os_memcpy(sta->supp_op_classes + 1, supp_op_classes,
		  supp_op_classes_len);
}
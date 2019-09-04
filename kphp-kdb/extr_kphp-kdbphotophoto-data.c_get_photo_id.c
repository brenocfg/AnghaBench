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
typedef  int /*<<< orphan*/  event ;
struct TYPE_2__ {int /*<<< orphan*/ * fields; } ;

/* Variables and functions */
 int* GET_INT (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t PHOTO_TYPE ; 
 size_t photo_type_id ; 
 TYPE_1__* types ; 

int get_photo_id (event *e) {
  return *GET_INT (e, &types[PHOTO_TYPE].fields[photo_type_id]);
}
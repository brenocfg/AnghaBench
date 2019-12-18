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
typedef  int /*<<< orphan*/  dyn_object ;
typedef  int /*<<< orphan*/  change ;

/* Variables and functions */
 int /*<<< orphan*/  PHOTO_TYPE ; 
 int my_add_change (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int photo_add_change (dyn_object **_o, change *_c) {
  return my_add_change (_o, _c, PHOTO_TYPE);
}
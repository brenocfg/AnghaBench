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
typedef  int /*<<< orphan*/  actual_object ;

/* Variables and functions */
 int /*<<< orphan*/  ALBUM_TYPE ; 
 int my_object_save (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 

int album_object_save (actual_object *o, char *buf, int buf_size) {
  return my_object_save (o, buf, buf_size, ALBUM_TYPE);
}
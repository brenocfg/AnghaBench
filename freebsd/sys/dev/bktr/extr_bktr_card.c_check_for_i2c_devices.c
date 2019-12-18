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
typedef  int /*<<< orphan*/  bktr_ptr_t ;

/* Variables and functions */
 int ABSENT ; 
 int i2cRead (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int check_for_i2c_devices( bktr_ptr_t bktr ){
  int x, temp_read;
  int i2c_all_0 = 1;
  int i2c_all_absent = 1;
  for ( x = 0; x < 128; ++x ) {
    temp_read = i2cRead( bktr, (2 * x) + 1 );
    if (temp_read != 0)      i2c_all_0 = 0;
    if (temp_read != ABSENT) i2c_all_absent = 0;
  }

  if ((i2c_all_0) || (i2c_all_absent)) return 0;
  else return 1;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int orientation; } ;
typedef  TYPE_1__ Image ;

/* Variables and functions */
#define  BottomRightOrientation 130 
#define  LeftBottomOrientation 129 
#define  RightTopOrientation 128 

__attribute__((used)) static void fix_angle_using_orientation (Image *image, int *angle) {
  switch (image->orientation) {
    case BottomRightOrientation:
      (*angle) += 2;
      break;
    case RightTopOrientation:
      (*angle) += 1;
      break;
    case LeftBottomOrientation:
      (*angle) += 3;
      break;
    default:
      break;
  }
}
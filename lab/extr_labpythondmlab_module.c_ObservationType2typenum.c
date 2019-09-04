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
typedef  int EnvCApi_ObservationType ;

/* Variables and functions */
#define  EnvCApi_ObservationBytes 130 
#define  EnvCApi_ObservationDoubles 129 
#define  EnvCApi_ObservationString 128 
 int NPY_DOUBLE ; 
 int NPY_UINT8 ; 

__attribute__((used)) static int ObservationType2typenum(EnvCApi_ObservationType type) {
  switch (type) {
    case EnvCApi_ObservationDoubles:
      return NPY_DOUBLE;
    case EnvCApi_ObservationBytes:
      return NPY_UINT8;
    case EnvCApi_ObservationString:
    default:
      return -1;
  }
}
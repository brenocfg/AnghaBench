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
typedef  scalar_t__* vec3_t ;
typedef  int byte ;

/* Variables and functions */
 float RAD2DEG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acos (scalar_t__) ; 
 int /*<<< orphan*/  atan2 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void NormalToLatLong(const vec3_t normal, byte out[2]) {
  // check for singularities
  if (normal[0] == 0 && normal[1] == 0) {
    if (normal[2] > 0) {
      out[0] = 0;
      out[1] = 0;       // lat = 0, long = 0
    } else {
      out[0] = 128;
      out[1] = 0;       // lat = 0, long = 128
    }
  } else {
    int a = RAD2DEG(atan2(normal[1], normal[0])) * (255.0f / 360.0f);
    int b = RAD2DEG(acos(normal[2])) * (255.0f / 360.0f);
    out[0] = b & 0xff;   // longitude
    out[1] = a & 0xff;   // latitude
  }
}
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
typedef  int* vec3_t ;
typedef  float byte ;

/* Variables and functions */
 int cosf (float) ; 
 float kPi ; 
 int sinf (float) ; 

__attribute__((used)) static void LatLongToNormal(byte normal[2], vec3_t out) {
  float phi = normal[0] * 2.0f * kPi / 255.0f;
  float theta = normal[1] * 2.0f * kPi / 255.0f;
  out[0] = cosf(theta) * sinf(phi);
  out[1] = sinf(theta) * sinf(phi);
  out[2] = cosf(phi);
}
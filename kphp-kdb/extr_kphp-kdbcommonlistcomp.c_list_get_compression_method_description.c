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

/* Variables and functions */
#define  le_degenerate 132 
#define  le_golomb 131 
#define  le_interpolative 130 
#define  le_interpolative_ext 129 
#define  le_llrun 128 

const char* list_get_compression_method_description (int compression_method) {
  switch (compression_method) {
  case le_degenerate:
    return "N == K";
  case le_golomb:
    return "Golomb";
  case le_interpolative:
    return "Interpolative";
  case le_interpolative_ext:
    return "Interpolative_ext";
  case le_llrun:
    return "LLRUN";
  default:
    return "Unknown";
  }
}
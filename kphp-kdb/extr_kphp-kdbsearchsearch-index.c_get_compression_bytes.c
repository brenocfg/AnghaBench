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
struct TYPE_2__ {long long* compression_bytes; } ;

/* Variables and functions */
 TYPE_1__ Header ; 

__attribute__((used)) static long long get_compression_bytes (int method) {
  return Header.compression_bytes[2*method] + Header.compression_bytes[2*method+1];
}
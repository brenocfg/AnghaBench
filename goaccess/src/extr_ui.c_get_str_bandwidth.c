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
struct TYPE_3__ {scalar_t__ resp_size; } ;
typedef  TYPE_1__ GLog ;

/* Variables and functions */
 char* filesize_str (float) ; 

__attribute__((used)) static char *
get_str_bandwidth (GLog * glog)
{
  return filesize_str ((float) glog->resp_size);
}
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
struct TYPE_2__ {int /*<<< orphan*/  sec; int /*<<< orphan*/  usec; int /*<<< orphan*/  w3c; int /*<<< orphan*/  apache; } ;

/* Variables and functions */
#define  AWSELB 137 
#define  AWSS3 136 
#define  CLOUDFRONT 135 
#define  CLOUDSTORAGE 134 
#define  COMBINED 133 
#define  COMMON 132 
#define  SQUID 131 
#define  VCOMBINED 130 
#define  VCOMMON 129 
#define  W3C 128 
 char* alloc_string (int /*<<< orphan*/ ) ; 
 TYPE_1__ dates ; 

char *
get_selected_date_str (size_t idx)
{
  char *fmt = NULL;
  switch (idx) {
  case COMMON:
  case VCOMMON:
  case COMBINED:
  case VCOMBINED:
  case AWSS3:
    fmt = alloc_string (dates.apache);
    break;
  case AWSELB:
  case CLOUDFRONT:
  case W3C:
    fmt = alloc_string (dates.w3c);
    break;
  case CLOUDSTORAGE:
    fmt = alloc_string (dates.usec);
    break;
  case SQUID:
    fmt = alloc_string (dates.sec);
    break;
  }

  return fmt;
}
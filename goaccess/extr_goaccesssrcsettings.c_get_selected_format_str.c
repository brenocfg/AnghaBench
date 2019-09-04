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
struct TYPE_2__ {int /*<<< orphan*/  awss3; int /*<<< orphan*/  squid; int /*<<< orphan*/  awselb; int /*<<< orphan*/  cloudstorage; int /*<<< orphan*/  cloudfront; int /*<<< orphan*/  w3c; int /*<<< orphan*/  vcombined; int /*<<< orphan*/  combined; int /*<<< orphan*/  vcommon; int /*<<< orphan*/  common; } ;

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
 TYPE_1__ logs ; 

char *
get_selected_format_str (size_t idx)
{
  char *fmt = NULL;
  switch (idx) {
  case COMMON:
    fmt = alloc_string (logs.common);
    break;
  case VCOMMON:
    fmt = alloc_string (logs.vcommon);
    break;
  case COMBINED:
    fmt = alloc_string (logs.combined);
    break;
  case VCOMBINED:
    fmt = alloc_string (logs.vcombined);
    break;
  case W3C:
    fmt = alloc_string (logs.w3c);
    break;
  case CLOUDFRONT:
    fmt = alloc_string (logs.cloudfront);
    break;
  case CLOUDSTORAGE:
    fmt = alloc_string (logs.cloudstorage);
    break;
  case AWSELB:
    fmt = alloc_string (logs.awselb);
    break;
  case SQUID:
    fmt = alloc_string (logs.squid);
    break;
  case AWSS3:
    fmt = alloc_string (logs.awss3);
    break;
  }

  return fmt;
}
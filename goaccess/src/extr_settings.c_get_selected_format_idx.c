#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * log_format; } ;
struct TYPE_3__ {int /*<<< orphan*/  awss3; int /*<<< orphan*/  squid; int /*<<< orphan*/  awselb; int /*<<< orphan*/  cloudstorage; int /*<<< orphan*/  cloudfront; int /*<<< orphan*/  w3c; int /*<<< orphan*/  vcombined; int /*<<< orphan*/  combined; int /*<<< orphan*/  vcommon; int /*<<< orphan*/  common; } ;

/* Variables and functions */
 size_t AWSELB ; 
 size_t AWSS3 ; 
 size_t CLOUDFRONT ; 
 size_t CLOUDSTORAGE ; 
 size_t COMBINED ; 
 size_t COMMON ; 
 size_t SQUID ; 
 size_t VCOMBINED ; 
 size_t VCOMMON ; 
 size_t W3C ; 
 TYPE_2__ conf ; 
 TYPE_1__ logs ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

size_t
get_selected_format_idx (void)
{
  if (conf.log_format == NULL)
    return -1;
  if (strcmp (conf.log_format, logs.common) == 0)
    return COMMON;
  else if (strcmp (conf.log_format, logs.vcommon) == 0)
    return VCOMMON;
  else if (strcmp (conf.log_format, logs.combined) == 0)
    return COMBINED;
  else if (strcmp (conf.log_format, logs.vcombined) == 0)
    return VCOMBINED;
  else if (strcmp (conf.log_format, logs.w3c) == 0)
    return W3C;
  else if (strcmp (conf.log_format, logs.cloudfront) == 0)
    return CLOUDFRONT;
  else if (strcmp (conf.log_format, logs.cloudstorage) == 0)
    return CLOUDSTORAGE;
  else if (strcmp (conf.log_format, logs.awselb) == 0)
    return AWSELB;
  else if (strcmp (conf.log_format, logs.squid) == 0)
    return SQUID;
  else if (strcmp (conf.log_format, logs.awss3) == 0)
    return AWSS3;
  else
    return -1;
}
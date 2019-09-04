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
struct TYPE_2__ {char* time_format; char* date_format; char* log_format; } ;

/* Variables and functions */
 char const* ERR_FORMAT_NO_DATE_FMT ; 
 char const* ERR_FORMAT_NO_LOG_FMT ; 
 char const* ERR_FORMAT_NO_TIME_FMT ; 
 TYPE_1__ conf ; 

const char *
verify_formats (void)
{
  if (conf.time_format == NULL || *conf.time_format == '\0')
    return ERR_FORMAT_NO_TIME_FMT;

  if (conf.date_format == NULL || *conf.date_format == '\0')
    return ERR_FORMAT_NO_DATE_FMT;

  if (conf.log_format == NULL || *conf.log_format == '\0')
    return ERR_FORMAT_NO_LOG_FMT;

  return NULL;
}
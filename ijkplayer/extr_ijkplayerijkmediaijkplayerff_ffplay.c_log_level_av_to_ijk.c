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
 int AV_LOG_DEBUG ; 
 int AV_LOG_ERROR ; 
 int AV_LOG_FATAL ; 
 int AV_LOG_INFO ; 
 int AV_LOG_PANIC ; 
 int AV_LOG_TRACE ; 
 int AV_LOG_VERBOSE ; 
 int AV_LOG_WARNING ; 
 int IJK_LOG_DEBUG ; 
 int IJK_LOG_ERROR ; 
 int IJK_LOG_FATAL ; 
 int IJK_LOG_INFO ; 
 int IJK_LOG_VERBOSE ; 
 int IJK_LOG_WARN ; 

__attribute__((used)) inline static int log_level_av_to_ijk(int av_level)
{
    int ijk_level = IJK_LOG_VERBOSE;
    if      (av_level <= AV_LOG_PANIC)      ijk_level = IJK_LOG_FATAL;
    else if (av_level <= AV_LOG_FATAL)      ijk_level = IJK_LOG_FATAL;
    else if (av_level <= AV_LOG_ERROR)      ijk_level = IJK_LOG_ERROR;
    else if (av_level <= AV_LOG_WARNING)    ijk_level = IJK_LOG_WARN;
    else if (av_level <= AV_LOG_INFO)       ijk_level = IJK_LOG_INFO;
    // AV_LOG_VERBOSE means detailed info
    else if (av_level <= AV_LOG_VERBOSE)    ijk_level = IJK_LOG_INFO;
    else if (av_level <= AV_LOG_DEBUG)      ijk_level = IJK_LOG_DEBUG;
    else if (av_level <= AV_LOG_TRACE)      ijk_level = IJK_LOG_VERBOSE;
    else                                    ijk_level = IJK_LOG_VERBOSE;
    return ijk_level;
}
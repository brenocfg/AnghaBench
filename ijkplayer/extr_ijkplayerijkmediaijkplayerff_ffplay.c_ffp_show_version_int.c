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
typedef  int /*<<< orphan*/  FFPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  FFP_VERSION_MODULE_NAME_LENGTH ; 
 scalar_t__ IJKVERSION_GET_MAJOR (unsigned int) ; 
 scalar_t__ IJKVERSION_GET_MICRO (unsigned int) ; 
 scalar_t__ IJKVERSION_GET_MINOR (unsigned int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void ffp_show_version_int(FFPlayer *ffp, const char *module, unsigned version)
{
    av_log(ffp, AV_LOG_INFO, "%-*s: %u.%u.%u\n",
           FFP_VERSION_MODULE_NAME_LENGTH, module,
           (unsigned int)IJKVERSION_GET_MAJOR(version),
           (unsigned int)IJKVERSION_GET_MINOR(version),
           (unsigned int)IJKVERSION_GET_MICRO(version));
}
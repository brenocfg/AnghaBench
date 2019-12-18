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
typedef  int UINT8 ;
typedef  scalar_t__ UINT16 ;

/* Variables and functions */

UINT16
AeBuildFullExceptionCode (
    UINT8                   Level,
    UINT16                  MessageId)
{

    /*
     * Error level is in the thousands slot (error/warning/remark, etc.)
     * Error codes are 0 - 999
     */
    return (((Level + 1) * 1000) + MessageId);
}
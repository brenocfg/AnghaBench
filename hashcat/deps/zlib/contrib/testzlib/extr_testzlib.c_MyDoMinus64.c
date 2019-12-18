#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ LowPart; scalar_t__ HighPart; } ;
typedef  TYPE_1__ LARGE_INTEGER ;

/* Variables and functions */

void MyDoMinus64(LARGE_INTEGER *R,LARGE_INTEGER A,LARGE_INTEGER B)
{
    R->HighPart = A.HighPart - B.HighPart;
    if (A.LowPart >= B.LowPart)
        R->LowPart = A.LowPart - B.LowPart;
    else
    {
        R->LowPart = A.LowPart - B.LowPart;
        R->HighPart --;
    }
}
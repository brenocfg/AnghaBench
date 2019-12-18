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

__attribute__((used)) static size_t ZDICT_totalSampleSize(const size_t* fileSizes, unsigned nbFiles)
{
    size_t total=0;
    unsigned u;
    for (u=0; u<nbFiles; u++) total += fileSizes[u];
    return total;
}
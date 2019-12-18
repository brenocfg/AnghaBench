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
typedef  int x ;

/* Variables and functions */
 int PKT_PAD ; 

__attribute__((used)) static inline int pad(int x)
{
        return ((x) + PKT_PAD - 1) & ~(PKT_PAD - 1) ;
}
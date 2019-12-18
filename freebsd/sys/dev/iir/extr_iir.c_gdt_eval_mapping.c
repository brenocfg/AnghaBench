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
typedef  int u_int32_t ;

/* Variables and functions */
 int GDT_BIGHEADS ; 
 int GDT_BIGSECS ; 
 int GDT_HEADS ; 
 int GDT_MAXCYLS ; 
 int GDT_MEDHEADS ; 
 int GDT_MEDSECS ; 
 int GDT_SECS ; 

__attribute__((used)) static void
gdt_eval_mapping(u_int32_t size, int *cyls, int *heads, int *secs)
{
    *cyls = size / GDT_HEADS / GDT_SECS;
    if (*cyls < GDT_MAXCYLS) {
        *heads = GDT_HEADS;
        *secs = GDT_SECS;
    } else {
        /* Too high for 64 * 32 */
        *cyls = size / GDT_MEDHEADS / GDT_MEDSECS;
        if (*cyls < GDT_MAXCYLS) {
            *heads = GDT_MEDHEADS;
            *secs = GDT_MEDSECS;
        } else {
            /* Too high for 127 * 63 */
            *cyls = size / GDT_BIGHEADS / GDT_BIGSECS;
            *heads = GDT_BIGHEADS;
            *secs = GDT_BIGSECS;
        }
    }
}
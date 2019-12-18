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
typedef  int /*<<< orphan*/  u8 ;
typedef  int limb ;
typedef  int* felem ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void felem_to_bin66(u8 out[66], const felem in)
{
    memset(out, 0, 66);
    (*((limb *) & out[0])) = in[0];
    (*((limb *) & out[7])) |= in[1] << 2;
    (*((limb *) & out[14])) |= in[2] << 4;
    (*((limb *) & out[21])) |= in[3] << 6;
    (*((limb *) & out[29])) = in[4];
    (*((limb *) & out[36])) |= in[5] << 2;
    (*((limb *) & out[43])) |= in[6] << 4;
    (*((limb *) & out[50])) |= in[7] << 6;
    (*((limb *) & out[58])) = in[8];
}